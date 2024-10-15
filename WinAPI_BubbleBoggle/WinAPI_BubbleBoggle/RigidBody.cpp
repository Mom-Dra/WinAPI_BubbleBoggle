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

		// 가속도
		accel = force / mass;

		// 속도
		velocity += accel * deltaTime;

		// 마찰력 적용
		Vector2 friction{ -velocity.GetNormalize() * fricCoeff * deltaTime };

		if (velocity.Size() <= friction.Size())
		{
			velocity = Vector2::Zero;
		}
		else
		{
			velocity += friction;
		}

		// 속도 제한 검사
		if (velocity.Size() > maxVelocity)
		{
			velocity.Normalize();
			velocity *= maxVelocity;
		}

		// 속도에 따른 이동
		Move();

		// 힘 초기화
		force = Vector2::Zero;
	}

	void RigidBody::Move() const noexcept
	{
		Vector2 pos{ owner->GetPos() };

		pos += velocity * TimeManager::GetInstance().GetDeltaTime();

		owner->SetPos(pos);
	}
}