#include "CollisionManager.h"
#include "SceneManager.h"

namespace MomDra
{
    CollisionManager& CollisionManager::GetInstance() noexcept
    {
        static CollisionManager instance;

        return instance;
    }

    void CollisionManager::Initialize() noexcept
    {

    }

    void CollisionManager::Update() noexcept
    {
        for (unsigned int row{ 0 }; row < static_cast<unsigned int>(Layer::LAST); ++row)
        {
            for (unsigned int col{ row }; col < static_cast<unsigned int>(Layer::LAST); ++col)
            {
                if (checkArr[row] & (1 << col))
                    CollisionLayerUpdate(static_cast<Layer>(row), static_cast<Layer>(col));
            }
        }
    }

    void CollisionManager::CheckLayer(const Layer& layer1, const Layer& layer2) noexcept
    {
        // 더 작은 값의 그룹 타입을 행으로
        // 큰 갑을 열(비트)로 사용
        unsigned int row = static_cast<unsigned int>(layer1);
        unsigned int col = static_cast<unsigned int>(layer2);

        if (row > col)
        {
            std::swap(row, col);
        }

        checkArr[row] ^= (1 << col);
    }

    void CollisionManager::Reset() noexcept
    {
        checkArr.fill(0);
    }

    void CollisionManager::CollisionLayerUpdate(const Layer& layer1, const Layer& layer2) noexcept
    {
        Scene* curScene{ SceneManager::GetInstance().GetCurrentScene() };
        const std::vector<std::unique_ptr<Object>>& layer1Vec{ curScene->GetLayerObject(layer1) };
        const std::vector<std::unique_ptr<Object>>& layer2Vec{ curScene->GetLayerObject(layer2) };

        for (const auto& layer1Obj : layer1Vec)
        {
            Collider* collider1{ layer1Obj->GetCollider() };
            if (collider1 == nullptr)
                continue;

            for (const auto& layer2Obj : layer2Vec)
            {
                Collider* collider2{ layer2Obj->GetCollider() };

                // 충돌체가 없거나, 자기 자신과의 충돌
                if (collider2 == nullptr || layer1Obj == layer2Obj)
                    continue;

                ColliderId id;
                id.leftId = collider1->GetId();
                id.rightId = collider2->GetId();

                auto it{ ColliderInfoMap.find(id.id) };

                if (it == ColliderInfoMap.end())
                {
                    ColliderInfoMap.insert({ id.id, false });
                    it = ColliderInfoMap.find(id.id);
                }

                // 충돌하는 경우
                if (IsCollision(collider1, collider2))
                {
                    if(it->second)
                    {
                        // 이전에도 충돌 하고 있었다

                        if (layer1Obj->IsDead() || layer2Obj->IsDead())
                        {
                            // 둘 중하나가 삭제 예정이라면, 충돌 해제시켜준다
                            collider1->OnCollisionExit(collider2);
                            collider2->OnCollisionExit(collider1);

                            it->second = false;
                        }
                        else
                        {
                            collider1->OnCollisionStay(collider2);
                            collider2->OnCollisionStay(collider1);
                        }
                    }
                    else
                    { // 충돌을 막 시작하는 시점
                        
                        if (!layer1Obj->IsDead() && !layer2Obj->IsDead())
                        {
                            // 둘 중하나가 삭제 예정이라면, 충돌하지 않은것으로 취급
                            collider1->OnCollisionEnter(collider2);
                            collider2->OnCollisionEnter(collider1);

                            it->second = true;
                        }
                    }
                }
                else
                {
                    // 현재 중돌하고 있지 않다
                    if (it->second)
                    {
                        // 이전에도 충돌 하고 있었다
                        // 충돌이 막 끝나는 시점
                        collider1->OnCollisionExit(collider2);
                        collider2->OnCollisionExit(collider1);

                        it->second = false;
                    }
                }
            }
        }
    }

    bool CollisionManager::IsCollision(Collider* laye1Col, Collider* layer2Col) const noexcept
    {
        Vector2 layer1Pos{ laye1Col->GetFinalPos() };
        Vector2 layer1Scale{ laye1Col->GetScale() };

        Vector2 layer2Pos{ layer2Col->GetFinalPos() };
        Vector2 layer2Scale{ layer2Col->GetScale() };

        if (std::abs(layer1Pos.X - layer2Pos.X) < (layer1Scale.X + layer2Scale.X) / 2.0f
            && std::abs(layer1Pos.Y - layer2Pos.Y) < (layer1Scale.Y + layer2Scale.Y) / 2.0f)
            return true;

        return false;
    }
}
