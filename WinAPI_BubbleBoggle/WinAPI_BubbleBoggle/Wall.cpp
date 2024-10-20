#include "Wall.h"

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

		switch (otherLayer)
		{
		case Layer::Player:
		{
			Collider* thisCollider{ GetCollider() };

			float length{ thisCollider->GetScale().X / 2.0f + other->GetScale().X / 2.0f };

			Vector2 pos{ 0.0f, otherObj->GetPos().Y };

			if (other->GetFinalPos().X < thisCollider->GetFinalPos().X)
				pos.X = thisCollider->GetFinalPos().X - length;
			else
				pos.X = thisCollider->GetFinalPos().X + length;

			otherObj->SetPos(pos);
		}
		break;
		}
	}

	void Wall::Update() noexcept
	{

	}
}