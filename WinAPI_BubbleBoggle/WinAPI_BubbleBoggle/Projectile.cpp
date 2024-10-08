#include "Projectile.h"
#include "TimeManager.h"

namespace MomDra
{
	Projectile::Projectile(const Vector2& pos, const Vector2& scale, const Layer& layer) : Object{ pos, scale, layer }
	{
		CreateCollider(Vector2{ 100.0f, 100.0f });
	}

	void Projectile::Update() noexcept
	{
		const Vector2 pos{ GetPos() };

		
		SetPos(pos + -Vector2::UnitX * 100.0f * TimeManager::GetInstance().GetDeltaTime());
	}

	void Projectile::Render(const HDC& hdc) const noexcept
	{
		Object::Render(hdc);
	}

	void Projectile::OnCollisionEnter(const Collider* other)
	{
		/*Object* otherObject{ other->GetObj() };

		if (otherObject->GetLayer() == Layer::MONSTER)
		{
			EventManager::GetInstance().Destory(this);
		}*/
	}
}
