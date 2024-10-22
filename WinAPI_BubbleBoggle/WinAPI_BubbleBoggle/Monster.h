#pragma once
#include "Object.h"
#include "AI.h"
#include "Ray.h"

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
		virtual void Enter(Monster& monster) noexcept = 0;
		virtual void Update(Monster& monster) noexcept = 0;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) = 0;
		virtual void OnCollisionExit(Monster& monster, const Collider* other) = 0;
		virtual void Exit(Monster& monster) noexcept = 0;
	};

	class MonsterMoveState : public MonsterState
	{
	private:
		float changeDirTime{ 0.0f };
		float jumpTime{ 0.0f };
		float forwardJumpTime{ 0.0f };

	public:
		explicit MonsterMoveState() noexcept = default;
		explicit MonsterMoveState(const MonsterMoveState& other) noexcept = default;

		virtual void Enter(Monster& monster) noexcept;
		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;
		virtual void OnCollisionExit(Monster& monster, const Collider* other) override;
		inline virtual void Exit(Monster& monster) noexcept {}

	private:
		explicit MonsterMoveState(const MonsterMoveState&& other) = delete;
		MonsterMoveState& operator=(const MonsterMoveState& other) = delete;
		MonsterMoveState& operator=(const MonsterMoveState&& other) = delete;

		void Move(Monster& monster, float deltaTime) noexcept;
	};

	class MonsterTraceState : public MonsterState
	{
	private:

	public:
		explicit MonsterTraceState() noexcept = default;
		explicit MonsterTraceState(const MonsterTraceState& other) noexcept = default;

		inline virtual void Enter(Monster& monster) noexcept {}
		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;
		virtual void OnCollisionExit(Monster& monster, const Collider* other) override
		{

		}
		inline virtual void Exit(Monster& monster) noexcept {}

	private:
		explicit MonsterTraceState(const MonsterTraceState&& other) = delete;
		MonsterTraceState& operator=(const MonsterTraceState& other) = delete;
		MonsterTraceState& operator=(const MonsterTraceState&& other) = delete;
	};

	class MonsterAngryState : public MonsterState
	{
	private:
		float changeDirTime{ 0.0f };
		float jumpTime{ 0.0f };
		float forwardJumpTime{ 0.0f };

	public:
		explicit MonsterAngryState() noexcept = default;
		explicit MonsterAngryState(const MonsterAngryState& other) noexcept = default;

		virtual void Enter(Monster& monster) noexcept;
		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;
		virtual void OnCollisionExit(Monster& monster, const Collider* other) override;
		inline virtual void Exit(Monster& monster) noexcept {}

	private:
		explicit MonsterAngryState(const MonsterAngryState&& other) = delete;
		MonsterAngryState& operator=(const MonsterAngryState& other) = delete;
		MonsterAngryState& operator=(const MonsterAngryState&& other) = delete;

		void Move(Monster& monster, float deltaTime) noexcept;
	};

	class MonsterHittedState : public MonsterState
	{
	private:
		float time{ 0.0f };

	public:
		explicit MonsterHittedState() noexcept = default;
		explicit MonsterHittedState(const MonsterHittedState& other) noexcept = default;

		virtual void Enter(Monster& monster) noexcept override;
		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;
		virtual void OnCollisionExit(Monster& monster, const Collider* other) override {}
		inline virtual void Exit(Monster& monster) noexcept {}

	private:
		explicit MonsterHittedState(const MonsterHittedState&& other) = delete;
		MonsterHittedState& operator=(const MonsterHittedState& other) = delete;
		MonsterHittedState& operator=(const MonsterHittedState&& other) = delete;
	};

	struct MonsterSetting
	{
		static constexpr inline float CHANGE_DIR_TIME{ 3.0f };
		static constexpr inline int CHANGE_DIR_POSSIBILITY{ 20 };
		static constexpr inline float SPEED{ 150.0f };
		static constexpr inline float JUMP_POWER{ 300.0f };
		static constexpr inline float PLAYER_FORWARD_RAY_DISTANCE{ 50.0f };
		static constexpr inline float JUMP_COOL_DOWN{ 5.0f };

		static constexpr inline float ANGRY_SPEED{ SPEED * 2 };

		// 정면에 땅이 있는지 체크, 나중에 Wall로 바꿔야 한다
		static constexpr inline float GROUND_RAY_DISTANCE{ 30.0f };

		// HittedState
		static constexpr inline float HITTED_SPEED{ 100.0f };
		
		static constexpr inline float PROJECTILE_1_TIME{ 10.0f };
		static constexpr inline float PROJECTILE_2_TIME{ 5.0f };
		static constexpr inline float PROJECTILE_3_TIME{ 2.5f };
		static constexpr inline float PROJECTILE_4_TIME{ 1.25f };

		static const inline std::wstring WALK_LEFT{ L"Monster_Walk_Left" };
		static const inline std::wstring WALK_RIGHT{ L"Monster_Walk_Right" };
		static const inline std::wstring WALK_ANGRY_LEFT{ L"Monster_Walk_Angry_Left" };
		static const inline std::wstring WALK_ANGRY_RIGHT{ L"Monster_Walk_Angry_Right" };

		static const inline std::wstring INPROJECTILE_1{ L"Monster_InProjectile_1" };
		static const inline std::wstring INPROJECTILE_2{ L"Monster_InProjectile_2" };
		static const inline std::wstring INPROJECTILE_3{ L"Monster_InProjectile_3" };
		static const inline std::wstring INPROJECTILE_4{ L"Monster_InProjectile_4" };

		static const inline std::wstring JUMP_LEFT{ L"Monster_Jump_Left" };
		static const inline std::wstring JUMP_RIGHT{ L"Monster_Jump_Right" };
		static const inline std::wstring JUMP_ANGRY_LEFT{ L"Monster_Jump_Angry_Left" };
		static const inline std::wstring JUMP_ANGRY_RIGHT{ L"Monster_Jump_Angry_Right" };
	};

	class Monster : public Object
	{
	private:
		MonsterMoveState moveState;
		//MonsterTraceState traceState;
		MonsterAngryState angryState;
		MonsterHittedState hittedState;
		MonsterState* currState{ &moveState };

		// 후에 Object로 빼도 괜찮을 듯
		Vector2 forwardDir{ Vector2::UnitX };
		Vector2 upDir{ Vector2{0.0f, -1.0f} };

		Player* player{ nullptr };
		bool onGround{ false };

	public:
		explicit Monster(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::Monster);

		inline virtual void Update() noexcept override { currState->Update(*this); }
		virtual void OnCollisionEnter(const Collider* other) override;
		virtual void OnCollisionExit(const Collider* other) override;

		inline Player* GetPlayer() const noexcept { return player; }
		inline const Vector2& GetForwardDir() const noexcept { return forwardDir; }
		inline const Vector2& GetUpDir() const noexcept { return upDir; }
		inline bool GetOnGround() const noexcept { return onGround; }

		inline void SetPlayer(Player* player) noexcept { this->player = player; }
		inline void SetForwardDir(const Vector2 forwardDir) noexcept { this->forwardDir = forwardDir; }
		inline void SetUpDir(const Vector2 forwardDir) noexcept { this->upDir = upDir; }
		inline void SetOnGround(bool onGround) noexcept { this->onGround = onGround; }

		void ChangeDir() noexcept;
		void GetintoProjectile() noexcept;

		inline void MoveForward(float speed) const noexcept { GetRigidBody()->AddForce(forwardDir * speed); }
		inline void Jump() const noexcept { GetRigidBody()->AddVelocity(Vector2{ 0.0f, -MonsterSetting::JUMP_POWER }); }
		inline void JumpForward() const noexcept { GetRigidBody()->AddVelocity(Vector2{ forwardDir.X * MonsterSetting::JUMP_POWER, -MonsterSetting::JUMP_POWER }); }
		bool CanJump() const noexcept;

		inline void ChangeToMoveState() { ChangeState(&moveState); }
		//inline void ChangeToTraceState() { currState = &traceState; }
		inline void ChangeToAngryState() { ChangeState(&angryState); }
		inline void ChangeToHittedState() { ChangeState(&hittedState); }

		inline virtual std::unique_ptr<Object> Clone() const override { return std::make_unique<Monster>(*this); }

	private:
		void ChangeState(MonsterState* state) noexcept;
	};
}
