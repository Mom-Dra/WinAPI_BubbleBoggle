#include "Monster.h"

namespace MomDra
{
	Monster::Monster(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath, const Layer& layer) : ImageObject{ pos, scale, imgPath, layer }
	{
		CreateCollider(Vector2{ 100.0f, 100.0f });
	}

	void Monster::OnCollisionEnter(const Collider* other)
	{
		const Object* otherObject{ other->GetObj() };

		if (otherObject->GetLayer() == Layer::PROJECTILE)
		{
			EventManager::GetInstance().Destory(this);
		}
	}
}