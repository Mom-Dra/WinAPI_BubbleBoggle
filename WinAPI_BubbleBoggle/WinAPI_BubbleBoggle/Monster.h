#pragma once
#include "Object.h"
#include "AI.h"

namespace MomDra
{
	class Monster;
	class Player;

	/*enum class MonsterState
	{
		IDLE,
		PATROL,
		TRACE,
		ATTACK,
		RUN,
		DEAD,
		LAST
	};*/

	class MonsterState
	{
	public:
		virtual void Update(Monster& monster) noexcept = 0;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) = 0;
	};

	class MonsterMoveState : public MonsterState
	{
	private:
		static constexpr inline float ChangeDirTime{ 3.0f };
		static constexpr inline int ChangeDirPossibility{ 20 };
		static constexpr inline float speed{ 150.0f };
		static constexpr inline float playerForwardRayDistance{ 50.0f };
		static constexpr inline float groundRayDistance{ 30.0f };

		float time{ 0.0f };

	public:
		explicit MonsterMoveState() noexcept = default;
		explicit MonsterMoveState(const MonsterMoveState& other) noexcept = default;

		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;

	private:
		explicit MonsterMoveState(const MonsterMoveState&& other) = delete;
		MonsterMoveState& operator=(const MonsterMoveState& other) = delete;
		MonsterMoveState& operator=(const MonsterMoveState&& other) = delete;

		void Move(Monster& monster, float deltaTime) const noexcept;
	};

	class MonsterTraceState : public MonsterState
	{
	private:

	public:
		explicit MonsterTraceState() noexcept = default;
		explicit MonsterTraceState(const MonsterTraceState& other) noexcept = default;

		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;

	private:
		explicit MonsterTraceState(const MonsterTraceState&& other) = delete;
		MonsterTraceState& operator=(const MonsterTraceState& other) = delete;
		MonsterTraceState& operator=(const MonsterTraceState&& other) = delete;
	};

	class MonsterAngryState : public MonsterState
	{
	private:

	public:
		explicit MonsterAngryState() noexcept = default;
		explicit MonsterAngryState(const MonsterAngryState& other) noexcept = default;

		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;

	private:
		explicit MonsterAngryState(const MonsterAngryState&& other) = delete;
		MonsterAngryState& operator=(const MonsterAngryState& other) = delete;
		MonsterAngryState& operator=(const MonsterAngryState&& other) = delete;
	};

	class MonsterHittedState : public MonsterState
	{
	private:
		static constexpr inline float speed{ 100.0f };
		float time{ 0.0f };

	public:
		explicit MonsterHittedState() noexcept = default;
		explicit MonsterHittedState(const MonsterHittedState& other) noexcept = default;

		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;

	private:
		explicit MonsterHittedState(const MonsterHittedState&& other) = delete;
		MonsterHittedState& operator=(const MonsterHittedState& other) = delete;
		MonsterHittedState& operator=(const MonsterHittedState&& other) = delete;
	};

	class Monster : public Object
	{
	private:
		MonsterMoveState moveState;
		MonsterTraceState traceState;
		MonsterAngryState angryState;
		MonsterHittedState hittedState;
		MonsterState* currState{ &moveState };

		// ÈÄ¿¡ Object·Î »©µµ ±¦ÂúÀ» µí
		Vector2 forwardDir{ Vector2::UnitX };
		Vector2 upDir{ Vector2{1.0f, -1.0f} };

		Player* player;

	public:
		explicit Monster(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::Monster);

		inline virtual void Update() noexcept override { currState->Update(*this); }

		inline virtual void OnCollisionEnter(const Collider* other) override { currState->OnCollisionEnter(*this, other); }

		inline Player* GetPlayer() const noexcept { return player; }
		inline const Vector2 GetForwardDir() const noexcept { return forwardDir; }
		inline const Vector2 GetUpDir() const noexcept { return upDir; }

		inline void SetPlayer(Player* player) noexcept { this->player = player; }
		inline void SetForwardDir(const Vector2 forwardDir) noexcept { this->forwardDir = forwardDir; }
		inline void SetUpDir(const Vector2 forwardDir) noexcept { this->upDir = upDir; }

		inline void ChangeDir() noexcept
		{
			RigidBody* rigid{ GetRigidBody() };
			Vector2 velocity{ rigid->GetVelocity() };
			velocity.X = -velocity.X;
			rigid->SetVelocity(velocity);

			forwardDir = -forwardDir;
			upDir.X = -upDir.X;
		}

		inline void ChangeToMoveState() { currState = &moveState; }
		inline void ChangeToTraceState() { currState = &traceState; }
		inline void ChangeToAngryState() { currState = &angryState; }
		inline void ChangeToHittedState() { currState = &hittedState; }

		inline virtual std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<Monster>(*this);
		}
	};
}
