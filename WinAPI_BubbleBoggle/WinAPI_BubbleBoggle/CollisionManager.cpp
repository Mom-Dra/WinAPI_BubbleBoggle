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
        for (unsigned int row = 0; row < static_cast<unsigned int>(Layer::LAST); ++row)
        {
            for (unsigned int col = 0; col < static_cast<unsigned int>(Layer::LAST); ++col)
            {

            }
        }
    }

    void CollisionManager::CheckGroup(const Layer& layer1, const Layer& layer2) const noexcept
    {
        // �� ���� ���� �׷� Ÿ���� ������
        // ū ���� ��(��Ʈ)�� ���
        unsigned int row = static_cast<unsigned int>(layer1);
        unsigned int col = static_cast<unsigned int>(layer2);

        if (row > col)
        {
            std::swap(row, col);
        }
    }

    void CollisionManager::Reset() const noexcept
    {

    }
}
