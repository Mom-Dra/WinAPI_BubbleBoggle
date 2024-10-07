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
                    CollisionGroupUpdate(static_cast<Layer>(row), static_cast<Layer>(col));
            }
        }
    }

    void CollisionManager::CheckGroup(const Layer& layer1, const Layer& layer2) noexcept
    {
        // �� ���� ���� �׷� Ÿ���� ������
        // ū ���� ��(��Ʈ)�� ���
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

    void CollisionManager::CollisionGroupUpdate(const Layer& layer1, const Layer& layer2) noexcept
    {
        Scene* curScene{ SceneManager::GetInstance().GetCurrentScene() };
        const std::vector<std::unique_ptr<Object>>& layer1Vec{ curScene->GetGroupObject(layer1) };
        const std::vector<std::unique_ptr<Object>>& layer2Vec{ curScene->GetGroupObject(layer2) };

        for (const auto& layer1Obj : layer1Vec)
        {
            Collider* collider1{ layer1Obj->GetCollider() };
            if (collider1 == nullptr)
                continue;

            for (const auto& layer2Obj : layer2Vec)
            {
                Collider* collider2{ layer2Obj->GetCollider() };

                // �浹ü�� ���ų�, �ڱ� �ڽŰ��� �浹
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

                // �浹�ϴ� ���
                if (IsCollision(collider1, collider2))
                {
                    if(it->second)
                    {
                        // �������� �浹 �ϰ� �־���
                        collider1->OnCollisionStay(collider2);
                        collider2->OnCollisionStay(collider1);
                    }
                    else
                    {
                        // �浹�� �� �����ϴ� ����
                        collider1->OnCollisionEnter(collider2);
                        collider2->OnCollisionEnter(collider1);

                        it->second = true;
                    }
                }
                else
                {
                    // ���� �ߵ��ϰ� ���� �ʴ�
                    if (it->second)
                    {
                        // �������� �浹 �ϰ� �־���
                        // �浹�� �� ������ ����
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
