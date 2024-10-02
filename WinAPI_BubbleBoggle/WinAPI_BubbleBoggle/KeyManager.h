#pragma once

#include <vector>
#include <array>

// 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다

// 키 입력 이벤트 처리
// tap, hold, away

namespace MomDra
{
	enum class KeyState
	{
		NONE, // 눌리지 않았고, 이전에도 눌리지 않은 상태
		TAP, // 막 누른 시점
		HOLD, // 누르고 있는
		AWAY // 막 땐 시점
	};

	enum class Key
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

		ALT,
		CTRL,
		LSHIFT,
		SPACE,
		ENTER,
		ESC,

		LAST
	};

	struct KeyInfo
	{
		KeyState state;
		bool prevPush; // 이전 프레임에 눌렸는지 안눌렸는지..
	};

	class KeyManager
	{
	private:
		static std::array<int, static_cast<int>(Key::LAST)> keyArr;
		std::array<KeyInfo, static_cast<int>(Key::LAST)> keyStates;

	public:
		static KeyManager& GetInstance() noexcept;
		void Initialize() noexcept;
		void Update() noexcept;

		inline const KeyState& GetKeyState(const Key& key) const noexcept
		{
			return keyStates[static_cast<int>(key)].state;
		}

		inline bool GetKeyDown(const Key& key) const noexcept
		{
			return keyStates[static_cast<int>(key)].state == KeyState::TAP;
		}

		inline bool GetKeyUp(const Key& key) const noexcept
		{
			return keyStates[static_cast<int>(key)].state == KeyState::AWAY;
		}

		inline bool GetKey(const Key& key) const noexcept
		{
			return keyStates[static_cast<int>(key)].state == KeyState::HOLD;
		}

	private:
		explicit KeyManager() noexcept = default;
		explicit KeyManager(const KeyManager& other) = delete;
		KeyManager& operator=(const KeyManager& other) = delete;
	};
}


