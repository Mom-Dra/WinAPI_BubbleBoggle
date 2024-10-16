#include "RigidBody.h"
#include "Object.h"
#include "Vector2.h"
#include "TimeManager.h"
#include "Object.h"

using namespace CK;

namespace MomDra
{
	RigidBody::RigidBody(Object* owner) noexcept : owner{ owner }, mass{ 1.0f }, fricCoeff{ 100.0f }, maxVelocity{ Vector2{100.0f, 300.0f} }, isGravity{ true }
	{

	}

	RigidBody::RigidBody(const RigidBody& other) noexcept : owner{ nullptr }, mass{ other.mass }, fricCoeff{ other.fricCoeff }, maxVelocity{ other.maxVelocity }, isGravity{ other.isGravity }
	{

	}

	void RigidBody::LateUpdate() noexcept
	{
		float deltaTime{ TimeManager::GetInstance().GetDeltaTime() };

		// 중력 적용
		if (isGravity)
		{
			accel += gravityAccel;
		}

		// 가속도
		accel += force / mass;

		// 마찰력 적용
		Vector2 frictionAccel{ velocity.GetNormalize() * -fricCoeff };
		accel += frictionAccel;

		// 마찰력이 더 큰 경우?
		/*if (velocity.Size() <= friction.Size())
		{
			velocity = Vector2::Zero;
		}
		else
		{
			velocity += friction;
		}*/

		// 속도
		velocity += accel * deltaTime;

		// 속도 제한 검사
		if (std::abs(velocity.X) > maxVelocity.X)
		{
			velocity.X = velocity.X / std::abs(velocity.X) * maxVelocity.X;
		}

		if (std::abs(velocity.Y) > maxVelocity.Y)
		{
			velocity.Y = velocity.Y / std::abs(velocity.Y) * maxVelocity.Y;
		}

		// 속도에 따른 이동
		Move();

		// 힘 초기화
		force = Vector2::Zero;
		accel = Vector2::Zero;
	}

	void RigidBody::Move() const noexcept
	{
		Vector2 pos{ owner->GetPos() };

		pos += velocity * TimeManager::GetInstance().GetDeltaTime();

		owner->SetPos(pos);
	}
}