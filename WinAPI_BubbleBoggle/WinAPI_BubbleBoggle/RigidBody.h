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

		float mass; // ����
		float fricCoeff; // ���� ���
		float maxVelocity; // �ִ� �ӷ�

		// F = M x A
		// V += A * DT

	public:
		explicit RigidBody(Object* owner) noexcept;
		explicit RigidBody(const RigidBody& other) noexcept;

		inline void SetOwner(Object* owner) noexcept { this->owner = owner; }
		inline void SetMass(float mass) noexcept { this->mass = mass; }
		inline void AddForce(const Vector2& force) noexcept { this->force += force; }
		inline void SetVelocity(const Vector2& velocity) noexcept { this->velocity = velocity; }
		inline void SetMaxVelocity(float maxVelocity) noexcept { this->maxVelocity = maxVelocity; }
		inline void AddVelocity(const Vector2& velocity) noexcept { this->velocity += velocity; }

		void LateUpdate() noexcept;

	private:
		void Move() const noexcept;
	};
}
