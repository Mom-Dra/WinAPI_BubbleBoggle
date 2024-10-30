#pragma once
#include "Object.h"
#include "AI.h"
#include "Ray.h"
#include "Vector2.h"

using namespace CK;

namespace MomDra
{
	class Monster;
	class Player;

	struct MonsterSetting
	{
		static constexpr inline float CHANGE_DIR_TIME{ 3.0f };
		static constexpr inline int CHANGE_DIR_POSSIBILITY{ 20 };
		static constexpr inline int JUMP_POSSIBILITY{ 3 };
		static constexpr inline int FORWARD_JUMP_POSSIBILITY{ 50 };
		static constexpr inline float SPEED{ 200.0f };
		static constexpr inline float FALL_SPEED{ 0.0f };
		static constexpr inline float JUMP_POWER{ 610.0f };
		static constexpr inline float JUMP_COOL_DOWN{ 5.0f };

		// Ray
		static constexpr inline float FORWARD_RAY_DISTANCE{ 30.0f };
		static constexpr inline float UP_RAY_DISTANCE{ 120.0f };
		static constexpr inline float DOWN_RAY_DISTANCE{ 30.0f };

		// Angry
		static constexpr inline float ANGRY_SPEED{ SPEED * 2 };

		// Hitted
		static constexpr inline float HITTED_SPEED{ 100.0f };

		// Animation
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

		static constexpr inline Vector2 SPAWN_POS{ 200.0f, 200.0f };
	};

	class MonsterState
	{
	public:
		virtual void Enter(Monster& monster) noexcept abstract;
		virtual void Update(Monster& monster) noexcept abstract;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) abstract;
		virtual void OnCollisionExit(Monster& monster, const Collider* other) abstract;
		virtual void Exit(Monster& monster) noexcept abstract;
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

		virtual void Enter(Monster& monster) noexcept override;
		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;
		virtual void OnCollisionExit(Monster& monster, const Collider* other) override;
		virtual void Exit(Monster& monster) noexcept override;

	private:
		explicit MonsterMoveState(MonsterMoveState&& other) = delete;
		MonsterMoveState& operator=(const MonsterMoveState& other) = delete;
		MonsterMoveState& operator=(MonsterMoveState&& other) = delete;

		void Move(Monster& monster, float deltaTime) noexcept;
		void WalkAnimation(Monster& monster);
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

		virtual void Enter(Monster& monster) noexcept override;
		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;
		virtual void OnCollisionExit(Monster& monster, const Collider* other) override;
		virtual void Exit(Monster& monster) noexcept override;

	private:
		explicit MonsterAngryState(MonsterAngryState&& other) = delete;
		MonsterAngryState& operator=(const MonsterAngryState& other) = delete;
		MonsterAngryState& operator=(MonsterAngryState&& other) = delete;

		void Move(Monster& monster, float deltaTime) noexcept;
		void WalkAnimation(Monster& monster);
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
		inline virtual void Exit(Monster& monster) noexcept override { time = 0.0f; }

	private:
		explicit MonsterHittedState(MonsterHittedState&& other) = delete;
		MonsterHittedState& operator=(const MonsterHittedState& other) = delete;
		MonsterHittedState& operator=(MonsterHittedState&& other) = delete;
	};

	class MonsterHighState : public MonsterState
	{
	private:
		float time{ 0.0f };
		float targetYpos{ 0.0f };

	public:
		explicit MonsterHighState() noexcept = default;
		explicit MonsterHighState(const MonsterHighState& other) noexcept = default;

		virtual void Enter(Monster& monster) noexcept override;
		virtual void Update(Monster& monster) noexcept override;
		virtual void OnCollisionEnter(Monster& monster, const Collider* other) override;
		virtual void OnCollisionExit(Monster& monster, const Collider* other) override {}
		inline virtual void Exit(Monster& monster) noexcept override { time = 0.0f; targetYpos = 0.0f; }

	private:
		explicit MonsterHighState(MonsterHittedState&& other) = delete;
		MonsterHighState& operator=(const MonsterHighState& other) = delete;
		MonsterHighState& operator=(MonsterHighState&& other) = delete;
	};

	class Monster : public Object
	{
	private:
		MonsterMoveState moveState;
		MonsterAngryState angryState;
		MonsterHittedState hittedState;
		MonsterHighState highState;
		MonsterState* currState{ &moveState };

		// ÈÄ¿¡ Object·Î »©µµ ±¦ÂúÀ» µí
		Vector2 forwardDir{ Vector2::UnitX };
		Vector2 upDir{ -Vector2::UnitY };

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

		inline bool IsRight() const noexcept { return forwardDir == Vector2::UnitX; }
		inline bool CheckFall() const noexcept { return GetRigidBody()->GetVelocity().Y > 0.0f; }

		void ChangeDir() noexcept;
		void GetintoProjectile() noexcept;
		void Die() noexcept;

		inline void MoveForward(float speed) const noexcept { GetRigidBody()->AddVelocity(forwardDir * speed); }
		inline void Jump() const noexcept { GetRigidBody()->AddVelocity(Vector2{ 0.0f, -MonsterSetting::JUMP_POWER }); }
		inline void JumpForward() const noexcept { GetRigidBody()->AddVelocity(Vector2{ forwardDir.X * MonsterSetting::JUMP_POWER, -MonsterSetting::JUMP_POWER / 1.5f }); }
		bool CanJump() const noexcept;

		inline void ChangeToMoveState() { ChangeState(&moveState); }
		inline void ChangeToAngryState() { ChangeState(&angryState); }
		inline void ChangeToHittedState() { ChangeState(&hittedState); }
		inline void ChangeToHighState() { ChangeState(&highState); }

		inline virtual std::unique_ptr<Object> Clone() const override { return std::make_unique<Monster>(*this); }

	private:
		void ChangeState(MonsterState* state) noexcept;
	};
}
