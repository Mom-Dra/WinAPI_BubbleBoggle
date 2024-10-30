#pragma once
#include "Vector2.h"

using namespace CK;

namespace MomDra
{
	class Object;

	class RigidBody
	{
	private:
		Object* owner;

		Vector2 force; // 크기, 방향
		Vector2 accel; // 가속도
		Vector2 velocity; // 속도( 크기: 속력, 방향)

		static inline constexpr Vector2 gravityAccel{ 0.0f, 1000.0f };
		Vector2 maxVelocity{ 100.0f, 1000.0f }; // 최대 속력

		float mass; // 질량
		float fricCoeff; // 마찰 계수

		bool isGravity;

		// F = M x A
		// V += A * DT

	public:
		explicit RigidBody(Object* owner) noexcept;
		explicit RigidBody(const RigidBody& other) noexcept;

		inline const Vector2& GetVelocity() const noexcept { return velocity; }
		inline const Vector2& GetMaxVelocity() const noexcept { return maxVelocity; }
		inline bool GetGravity() const noexcept { return isGravity; }

		inline void SetOwner(Object* owner) noexcept { this->owner = owner; }
		inline void SetMass(float mass) noexcept { this->mass = mass; }
		inline void SetVelocity(const Vector2& velocity) noexcept { this->velocity = velocity; }
		inline void SetMaxVelocity(const Vector2& maxVelocity) noexcept { this->maxVelocity = maxVelocity; }
		inline void SetGravity(bool isGravity) noexcept { this->isGravity = isGravity; }

		inline void AddForce(const Vector2& force) noexcept { this->force += force; }
		inline void AddVelocity(const Vector2& velocity) noexcept { this->velocity += velocity; }

		void LateUpdate() noexcept;

	private:
		void Move() const noexcept;
	};
}
