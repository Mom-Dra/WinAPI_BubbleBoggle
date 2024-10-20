#include "Ground.h"
#include "Player.h"
#include "Monster.h"

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

		float yPos{ thisCollider->GetFinalPos().Y - thisCollider->GetScale().Y / 2.0f - other->GetScale().Y / 2.0f + 0.01f };

		switch (otherLayer)
		{
		case Layer::Player:
		{
			// rigidbody �ʿ� ���̶�� ����!

			// ���� ����
			if (std::abs(other->GetFinalPos().X - thisCollider->GetFinalPos().X) >= other->GetScale().X / 2.0f + thisCollider->GetScale().X / 2.0f - 0.2f)
				return;

			// �Ʒ����� ���� �ö󰡴� ��� ����!
			if (rigid->GetVelocity().Y < 0.0f && thisCollider->GetFinalPos().Y < other->GetFinalPos().Y) return;


			rigid->SetGravity(false);
			rigid->SetVelocity(Vector2{ rigid->GetVelocity().X, 0.0f });
			otherObj->SetPos(Vector2{ otherObj->GetPos().X, yPos });
		}
			break;

		case Layer::Monster:

			// �Ʒ��� ���� ���� �� ��
			if (rigid->GetVelocity().Y < 0.0f && thisCollider->GetFinalPos().Y < other->GetFinalPos().Y) return;

			// ���Ͱ� ���� ���� ��
			if (other->GetFinalPos().Y < thisCollider->GetFinalPos().Y)
				dynamic_cast<Monster*>(otherObj)->SetOnGround(true);

			rigid->SetGravity(false);
			rigid->SetVelocity(Vector2{ rigid->GetVelocity().X, 0.0f });
			otherObj->SetPos(Vector2{ otherObj->GetPos().X, yPos });
			break;

		case Layer::Item:
			rigid->SetGravity(false);
			rigid->SetVelocity(Vector2{ rigid->GetVelocity().X, 0.0f });

			otherObj->SetPos(Vector2{ otherObj->GetPos().X, yPos });
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
		case Layer::Player:
		{
			float left{ other->GetFinalPos().Y + other->GetScale().Y / 2.0f };
			float right{ thisCollider->GetFinalPos().Y - thisCollider->GetScale().Y / 2.0f + 0.4f };

			float left2{ std::abs(other->GetFinalPos().X - thisCollider->GetFinalPos().X) };
			float right2{ other->GetScale().X / 2.0f + thisCollider->GetScale().X / 2.0f - 0.01f };

			// �� �鿡 �ε����� ��
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
		case Layer::Monster:
			break;
		}
	}

	void Ground::OnCollisionExit(const Collider* other)
	{
		Object* otherObj{ other->GetObj() };
		const Layer& otherLayer{ otherObj->GetLayer() };
		RigidBody* rigid{ otherObj->GetRigidBody() };

		switch (otherLayer)
		{
		case Layer::Player:
			rigid->SetGravity(true);
			break;
		case Layer::Monster:
			rigid->SetGravity(true);	
			dynamic_cast<Monster*>(otherObj)->SetOnGround(false);
			break;
		}
	}
}