#include "RigidBody.h"
#include "Object.h"
#include "Vector2.h"
#include "TimeManager.h"
#include "Object.h"

using namespace CK;

namespace MomDra
{
	RigidBody::RigidBody(Object* owner) noexcept : owner{ owner }, mass{ 1.0f }, fricCoeff{ 100.0f }, maxVelocity{ 100.0f }
	{

	}

	RigidBody::RigidBody(const RigidBody& other) noexcept : owner{ nullptr }, mass{ other.mass }, fricCoeff{ other.fricCoeff }, maxVelocity{ other.maxVelocity }
	{

	}

	void RigidBody::LateUpdate() noexcept
	{
		float deltaTime{ TimeManager::GetInstance().GetDeltaTime() };

		// ���ӵ�
		accel = force / mass;

		// �ӵ�
		velocity += accel * deltaTime;

		// ������ ����
		Vector2 friction{ -velocity.GetNormalize() * fricCoeff * deltaTime };

		if (velocity.Size() <= friction.Size())
		{
			velocity = Vector2::Zero;
		}
		else
		{
			velocity += friction;
		}

		// �ӵ� ���� �˻�
		if (velocity.Size() > maxVelocity)
		{
			velocity.Normalize();
			velocity *= maxVelocity;
		}

		// �ӵ��� ���� �̵�
		Move();

		// �� �ʱ�ȭ
		force = Vector2::Zero;
	}

	void RigidBody::Move() const noexcept
	{
		Vector2 pos{ owner->GetPos() };

		pos += velocity * TimeManager::GetInstance().GetDeltaTime();

		owner->SetPos(pos);
	}
}