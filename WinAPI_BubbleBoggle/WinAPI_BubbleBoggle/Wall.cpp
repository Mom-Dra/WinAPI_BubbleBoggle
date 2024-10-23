#include "Wall.h"
#include "Core.h"
#include "Monster.h"

namespace MomDra
{
	Wall::Wall(const Vector2& pos, const Vector2& scale, const Layer& layer) : Object{ pos, scale, layer }
	{
		CreateCollider(scale);
	}

	void Wall::OnCollisionStay(const Collider* other)
	{
		Object* otherObj{ other->GetObj() };
		const Layer& otherLayer{ otherObj->GetLayer() };
		const Vector2& otherPos{ otherObj->GetPos() };

		Collider* thisCollider{ GetCollider() };
		float length{ thisCollider->GetScale().X / 2.0f + other->GetScale().X / 2.0f };
		Vector2 pos{ 0.0f, otherPos.Y };

		if (other->GetFinalPos().X < thisCollider->GetFinalPos().X)
			pos.X = thisCollider->GetFinalPos().X - length;
		else
			pos.X = thisCollider->GetFinalPos().X + length;

		switch (otherLayer)
		{
		case Layer::Player:
			otherObj->SetPos(pos);
		break;
		case Layer::Projectile:
			if (other->GetFinalPos().Y > thisCollider->GetFinalPos().Y)
			{
				static int halfWidth{ Core::WINDOW_WIDTH / 2 };
				Vector2 yPos{ otherObj->GetPos().X, thisCollider->GetFinalPos().Y + thisCollider->GetScale().Y };

				if (halfWidth > otherPos.X)
					yPos.X += TimeManager::GetInstance().GetDeltaTime() * 1000.0f;
				else
					yPos.X -= TimeManager::GetInstance().GetDeltaTime() * 1000.0f;

				otherObj->SetPos(yPos);
			}
			else
			{
				otherObj->SetPos(pos);
			}
			break;
		case Layer::Monster:
		{
			if (other->GetFinalPos().Y > thisCollider->GetFinalPos().Y)
			{
				static int halfWidth{ Core::WINDOW_WIDTH / 2 };
				Vector2 yPos{ otherObj->GetPos().X, thisCollider->GetFinalPos().Y + thisCollider->GetScale().Y };

				if (halfWidth > otherPos.X)
					yPos.X += TimeManager::GetInstance().GetDeltaTime() * MonsterSetting::HITTED_SPEED;
				else
					yPos.X -= TimeManager::GetInstance().GetDeltaTime() * MonsterSetting::HITTED_SPEED;

				otherObj->SetPos(yPos);
			}
			else
			{
				otherObj->SetPos(pos);
			}
		}
			break;
		}
	}

	void Wall::Update() noexcept
	{

	}
}