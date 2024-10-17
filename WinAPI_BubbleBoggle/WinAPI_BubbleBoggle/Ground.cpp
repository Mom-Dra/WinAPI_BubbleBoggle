#include "Ground.h"
#include "Player.h"

namespace MomDra
{
	Ground::Ground(const Vector2& pos, const Vector2& scale, const Layer& layer) : Object{ pos, scale, layer }
	{
		CreateCollider(scale);
	}

	void Ground::Start()
	{

	}

	void Ground::Update() noexcept
	{

	}

	void Ground::OnCollisionEnter(const Collider* other)
	{
		Object* otherObj{ other->GetObj() };
		const Layer& otherLayer{ otherObj->GetLayer() };
		Collider* thisCollider{ GetCollider() };
		RigidBody* rigid{ otherObj->GetRigidBody() };

		switch (otherLayer)
		{
		case Layer::PLAYER:
		{
			// rigidbody ÂÊ¿¡ ¶¥ÀÌ¶ó°í ¼³Á¤!
			if (std::abs(other->GetFinalPos().X - thisCollider->GetFinalPos().X) >= other->GetScale().X / 2.0f + thisCollider->GetScale().X / 2.0f - 0.2f)
				return;

			rigid->SetGravity(false);
			rigid->SetVelocity(Vector2{ rigid->GetVelocity().X, 0.0f });

			float yPos{ thisCollider->GetFinalPos().Y - thisCollider->GetScale().Y / 2.0f - other->GetScale().Y / 2.0f + 0.01f };

			otherObj->SetPos(Vector2{ otherObj->GetPos().X, yPos });
		}
			break;
		case Layer::MONSTER:
			
			break;
		}
	}

	void Ground::OnCollisionStay(const Collider* other)
	{
		Object* otherObj{ other->GetObj() };
		const Layer& otherLayer{ otherObj->GetLayer() };
		Collider* thisCollider{ GetCollider() };
		RigidBody* rigid{ otherObj->GetRigidBody() };

		switch (otherLayer)
		{
		case Layer::PLAYER:
		{
			float left{ other->GetFinalPos().Y + other->GetScale().Y / 2.0f };
			float right{ thisCollider->GetFinalPos().Y - thisCollider->GetScale().Y / 2.0f + 0.4f };

			float left2{ std::abs(other->GetFinalPos().X - thisCollider->GetFinalPos().X) };
			float right2{ other->GetScale().X / 2.0f + thisCollider->GetScale().X / 2.0f - 0.01f };

			// º® ¸é¿¡ ºÎµúÃÆÀ» ¶§
			if (other->GetFinalPos().Y + other->GetScale().Y / 2.0f > thisCollider->GetFinalPos().Y - thisCollider->GetScale().Y / 2.0f + 0.2f)
			{
				if (std::abs(other->GetFinalPos().X - thisCollider->GetFinalPos().X) > other->GetScale().X / 2.0f + thisCollider->GetScale().X / 2.0f -  0.2f)
				{
					rigid->SetVelocity(Vector2{ 0.0f, rigid->GetVelocity().Y });
				}
				else rigid->SetGravity(false);
			}
			else
			{
				rigid->SetGravity(false);
			}
		}
			break;
		case Layer::MONSTER:
			break;
		}
	}

	void Ground::OnCollisionExit(const Collider* other)
	{
		Object* otherObj{ other->GetObj() };
		const Layer& otherLayer{ otherObj->GetLayer() };

		switch (otherLayer)
		{
		case Layer::PLAYER:
		{
			Player* player{ dynamic_cast<Player*>(otherObj) };

			RigidBody* rigid{ otherObj->GetRigidBody() };
			rigid->SetGravity(true);
		}
			break;
		case Layer::MONSTER:
			break;
		}
	}
}