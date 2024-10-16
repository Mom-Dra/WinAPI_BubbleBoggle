#include "Ground.h"

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
			// rigidbody 쪽에 땅이라고 설정!
			if (std::abs(other->GetFinalPos().X - thisCollider->GetFinalPos().X) >= other->GetScale().X / 2.0f + thisCollider->GetScale().X / 2.0f - 0.2f)
				return;

			rigid->SetGravity(false);
			rigid->SetVelocity(Vector2{ rigid->GetVelocity().X, 0.0f });

			float yPos{ thisCollider->GetFinalPos().Y - thisCollider->GetScale().Y / 2.0f - other->GetScale().Y / 2.0f + 0.1f };

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
			if (other->GetFinalPos().Y + other->GetScale().Y / 2.0f > thisCollider->GetFinalPos().Y - thisCollider->GetScale().Y / 2.0f + 0.2f)
			{
				if (std::abs(other->GetFinalPos().X - thisCollider->GetFinalPos().X) > other->GetScale().X / 2.0f + thisCollider->GetScale().X / 2.0f - 0.2f)
				{
					rigid->SetVelocity(Vector2{ 0.0f, rigid->GetVelocity().Y });
				}
			}
			break;
		case Layer::MONSTER:
			break;
		}
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
			RigidBody* rigid{ otherObj->GetRigidBody() };
			rigid->SetGravity(true);
		}
			break;
		case Layer::MONSTER:
			break;
		}
	}
}