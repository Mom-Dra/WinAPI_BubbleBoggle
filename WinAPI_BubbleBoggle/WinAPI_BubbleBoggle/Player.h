#pragma once
#include "Object.h"

namespace MomDra
{
	class Player;

	struct PlayerSetting
	{
		static const inline std::wstring IDLE_LEFT{ L"Player_Idle_Left" };
		static const inline std::wstring WALK_LEFT{ L"Player_Walk_Left" };
		static const inline std::wstring FALL_LEFT{ L"Player_Fall_Left" };
		static const inline std::wstring JUMP_LEFT{ L"Player_Jump_Left" };
		static const inline std::wstring ATTACK_LEFT{ L"Player_Attack_Left" };
		static const inline std::wstring HIT_LEFT{ L"Player_Hit_Left" }; // 처음 맞았을 때
		static const inline std::wstring ROTATE_1{ L"Player_Rotate_1_Left" }; // LEFT, RIGHT 공통
		static const inline std::wstring ROTATE_2{ L"Player_Rotate_2_Left" }; // LEFT, RIGHT 공통
		static const inline std::wstring DESTROY{ L"Player_Destroy" };

		static const inline std::wstring IDLE_RIGHT{ L"Player_Idle_Right" };
		static const inline std::wstring WALK_RIGHT{ L"Player_Walk_Right" };
		static const inline std::wstring FALL_RIGHT{ L"Player_Fall_Right" };
		static const inline std::wstring JUMP_RIGHT{ L"Player_Jump_Right" };
		static const inline std::wstring ATTACK_RIGHT{ L"Player_Attack_Right" };
		static const inline std::wstring HIT_RIGHT{ L"Player_Hit_Right" };

		static constexpr inline float MOVE_POWER{ 200.0f };
		static constexpr inline float FALL_MOVE_POWER{ 1.0f };
		static constexpr inline float JUMP_POWER{ 610.0f };

		static constexpr inline float HIT_TIME{ 0.5f };
		static constexpr inline float ROTATE_1_TIME{ 1.0f };
		static constexpr inline float ROTATE_2_TIME{ 1.0f };
		static constexpr inline float DESTROY_TIME{ 1.0f };

		static constexpr inline int LIFE{ 3 };
	};

	class PlayerState
	{
	public:
		virtual void Enter(Player& player) abstract;
		virtual void Update(Player& player) abstract;
		virtual void Exit(Player& player) abstract;

		virtual void OnCollisionEnter(Player& player, const Collider* other) abstract;
	};

	class PlayerIdleState : public PlayerState
	{
	public:
		explicit PlayerIdleState() noexcept = default;
		explicit PlayerIdleState(const PlayerIdleState& other) noexcept = default;

		virtual void Enter(Player& player) override;
		virtual void Update(Player& player) override;
		virtual void Exit(Player& player) override;

		inline virtual void OnCollisionEnter(Player& player, const Collider* other) override {}

	private:
		explicit PlayerIdleState(PlayerIdleState&& other) noexcept = delete;
		PlayerIdleState& operator=(const PlayerIdleState& other) noexcept = delete;
		PlayerIdleState& operator=(PlayerIdleState&& other) noexcept = delete;
	};

	class PlayerFallState : public PlayerState
	{
	public:
		explicit PlayerFallState() noexcept = default;
		explicit PlayerFallState(const PlayerFallState& other) noexcept = default;

		virtual void Enter(Player& player) override;
		virtual void Update(Player& player) override;
		virtual void Exit(Player& player) override;

		virtual void OnCollisionEnter(Player& player, const Collider* other) override;

	private:
		explicit PlayerFallState(PlayerFallState&& other) noexcept = delete;
		PlayerFallState& operator=(const PlayerFallState& other) noexcept = delete;
		PlayerFallState& operator=(PlayerFallState&& other) noexcept = delete;

		void FallAnimation(Player& player);
	};

	class PlayerJumpState : public PlayerState
	{
	public:
		explicit PlayerJumpState() noexcept = default;
		explicit PlayerJumpState(const PlayerJumpState& other) noexcept = default;

		virtual void Enter(Player& player) override;
		virtual void Update(Player& player) override;
		virtual void Exit(Player& player) override;

		inline virtual void OnCollisionEnter(Player& player, const Collider* other) override {}

	private:
		explicit PlayerJumpState(PlayerJumpState&& other) noexcept = delete;
		PlayerJumpState& operator=(const PlayerJumpState& other) noexcept = delete;
		PlayerJumpState& operator=(PlayerJumpState&& other) noexcept = delete;

		void JumpAnimation(Player& player);
	};

	class PlayerDeadState : public PlayerState
	{
	private:
		float time{ 0.0f };
		bool isPlayedDestroyAnim{ false };

	public:
		explicit PlayerDeadState() noexcept = default;
		explicit PlayerDeadState(const PlayerDeadState& other) noexcept = default;

		virtual void Enter(Player& player) override;
		virtual void Update(Player& player) override;
		virtual void Exit(Player& player) override;

		inline virtual void OnCollisionEnter(Player& player, const Collider* other) override {}

	private:
		explicit PlayerDeadState(PlayerDeadState&& other) noexcept = delete;
		PlayerDeadState& operator=(const PlayerDeadState& other) noexcept = delete;
		PlayerDeadState& operator=(PlayerDeadState&& other) noexcept = delete;
	};

	class Player : public Object
	{
	private:
		Vector2 forward{ Vector2::UnitX };
		bool isCollideSideOfGround{ false };

		PlayerIdleState idleState;
		PlayerFallState fallState;
		PlayerJumpState jumpState;
		PlayerDeadState deadState;
		PlayerState* currState;

		int life{ PlayerSetting::LIFE };

	public:
		explicit Player(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::PLAYER) noexcept;

		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		inline bool IsCollideSideOfGround() const noexcept { return isCollideSideOfGround; }

		inline bool IsRight() const noexcept { return forward == Vector2::UnitX; }
		void Die() noexcept;

		inline void DecreaseLife() noexcept { if (IsDead()) return; --life; }
		inline bool IsDead() const noexcept { return life == 0; }

		inline void SetIsCollideSideOfGround(bool isCollideSideOfGround) noexcept { this->isCollideSideOfGround = isCollideSideOfGround; }
		
		virtual void OnCollisionEnter(const Collider* other) override;
		virtual void OnCollisionStay(const Collider* other) override;
		virtual void OnCollisionExit(const Collider* other) override;

		inline void ChangeToIdleState() noexcept { ChangeState(&idleState); }
		inline void ChangeToFallState() noexcept { ChangeState(&fallState); }
		inline void ChangeToJumpState() noexcept { ChangeState(&jumpState); }
		inline void ChangeToDeadState() noexcept { ChangeState(&deadState); }

		inline virtual std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<Player>(*this);
		}

	public:
		void Move();
		void FallMove();
		void Attack() const noexcept;
		void Jump();
		void CheckFall();

	private:
		void ChangeState(PlayerState* state) noexcept;
	};
}
