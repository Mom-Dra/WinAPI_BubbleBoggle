#pragma once
#include "Object.h"
#include <coroutine>

namespace MomDra
{
	class Projectile;

	class ProjectileState
	{
	public:

	public:
		virtual void Enter(Projectile& projectile) noexcept = 0;
		virtual void Render(const Projectile& projectile, const HDC& hdc) const noexcept = 0;
		virtual void Update(Projectile& projectile) = 0;
		virtual void OnCollisionEnter(Projectile& projectile, const Collider* other) = 0;
		virtual void Exit(Projectile& projectile) noexcept = 0;
	};

	class ProjectileAttackState : public ProjectileState
	{
	private:
		static constexpr inline float speed{ 300.0f };
		static constexpr inline float moveTime{ 0.5f };
		float time{ 0.0f };

	public:
		explicit ProjectileAttackState() noexcept = default;
		explicit ProjectileAttackState(const ProjectileAttackState& other) noexcept = default;

		virtual void Enter(Projectile& projectile) noexcept override;

		inline virtual void Render(const Projectile& projectile, const HDC& hdc) const noexcept override
		{

		}

		virtual void Update(Projectile& projectile) override;

		inline virtual void OnCollisionEnter(Projectile& projectile, const Collider* other) override;

		inline virtual void Exit(Projectile& projectile) noexcept override {}

	private:
		explicit ProjectileAttackState(const ProjectileAttackState&& other) = delete;
		ProjectileAttackState& operator=(const ProjectileAttackState& other) = delete;
		ProjectileAttackState& operator=(const ProjectileAttackState&& other) = delete;
	};

	class ProjectileMovingState : public ProjectileState
	{
	private:
		static constexpr inline float speed{ 100.0f };
		static constexpr inline float moveTime{ 10.0f };
		float time{ 0.0f };

	public:
		explicit ProjectileMovingState() noexcept = default;
		explicit ProjectileMovingState(const ProjectileMovingState& other) noexcept = default;

		virtual void Enter(Projectile& projectile) noexcept override;
		inline virtual void Render(const Projectile& projectile, const HDC& hdc) const noexcept override
		{

		}

		virtual void Update(Projectile& projectile) override;

		inline virtual void OnCollisionEnter(Projectile& projectile, const Collider* other) override
		{

		}

		inline virtual void Exit(Projectile& projectile) noexcept override {}

	private:
		explicit ProjectileMovingState(const ProjectileMovingState&& other) = delete;
		ProjectileMovingState& operator=(const ProjectileMovingState& other) = delete;
		ProjectileMovingState& operator=(const ProjectileMovingState&& other) = delete;
	};

	class Projectile : public Object
	{
	private:
		ProjectileAttackState attackState;
		ProjectileMovingState movingState;

		ProjectileState* currState{ &attackState };
		Vector2 initialDir;

	public:
		inline explicit Projectile(const Vector2& pos, const Vector2& scale, const Vector2& initialDir, const Layer& layer = Layer::Projectile) : Object{ pos, scale, layer }, initialDir{ initialDir }
		{
			CreateCollider(scale);
		}

		inline Vector2 GetInitialDir() const noexcept { return initialDir; }

		inline virtual void Update() noexcept override { currState->Update(*this); }

		inline virtual void Render(const HDC& hdc) const noexcept override
		{
			Object::Render(hdc);
			currState->Render(*this, hdc);
		}

		inline virtual void OnCollisionEnter(const Collider* other) override
		{
			currState->OnCollisionEnter(*this, other);
		}

		inline bool IsAttackState() const noexcept { return currState == &attackState; }

		inline void ChangeToAttackState() { currState = &attackState; }
		inline void ChangeToMovingState() { currState = &movingState; }

		inline virtual std::unique_ptr<Object> Clone() const
		{
			return std::make_unique<Projectile>(*this);
		}
	};
}
