#include "CollisionManager.h"

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
                {

                }
            }
        }
    }

    void CollisionManager::CheckGroup(const Layer& layer1, const Layer& layer2) noexcept
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
}
