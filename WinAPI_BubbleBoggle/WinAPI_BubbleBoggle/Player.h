#pragma once
#include "Object.h"

namespace MomDra
{
	class Player;

	struct PlayerSetting
	{
		/*static constexpr float abc;
		static constexpr float aaa;
		static constexpr float aaaaa;

		static constexpr float bbbb;*/
		static const inline std::wstring IDLE{ L"Player_Idle_Left" };
		static const inline std::wstring WALK{ L"Player_Walk_Left" };
		static const inline std::wstring FALL{ L"Player_Falling_Left" };
		static const inline std::wstring JUMP{ L"Player_Jump_Left" };
		//static const inline std::wstring HIT_1{ L"Player_Hit_1_Left" };

		static const inline std::wstring ATTACK{ L"Player_Attack_Left" };
		static const inline std::wstring HIT{ L"Player_Hit_2_Left" }; // 처음 맞았을 때
		static const inline std::wstring ROTATE{ L"Player_Rotate_Left" };
		static const inline std::wstring ROTATE_2{ L"Player_Rotate_2_Left" };
		static const inline std::wstring DESTROY{ L"Player_Destroy" };
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
	};

	class PlayerDeadState : public PlayerState
	{
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
		Vector2 forward{ -Vector2::UnitX };
		bool isGround;

		PlayerIdleState idleState;
		PlayerFallState fallState;
		PlayerJumpState jumpState;
		PlayerDeadState deadState;
		PlayerState* currState{ &idleState };

	public:
		explicit Player(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::Player) noexcept;

		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

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
		void Fall();

	private:
		void ChangeState(PlayerState* state) noexcept;
	};
}
