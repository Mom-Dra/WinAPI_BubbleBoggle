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

		Vector2 force; // ũ��, ����
		Vector2 accel; // ���ӵ�
		Vector2 velocity; // �ӵ�( ũ��: �ӷ�, ����)

		static inline constexpr Vector2 gravityAccel{ 0.0f, 500.0f };

		float mass; // ����
		float fricCoeff; // ���� ���
		Vector2 maxVelocity; // �ִ� �ӷ�

		bool isGravity;

		// F = M x A
		// V += A * DT

	public:
		explicit RigidBody(Object* owner) noexcept;
		explicit RigidBody(const RigidBody& other) noexcept;

		inline const Vector2& GetVelocity() const noexcept { return velocity; }
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
