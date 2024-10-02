#pragma once

#include <vector>
#include <array>

// ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ��������

// Ű �Է� �̺�Ʈ ó��
// tap, hold, away

namespace MomDra
{
	enum class KeyState
	{
		NONE, // ������ �ʾҰ�, �������� ������ ���� ����
		TAP, // �� ���� ����
		HOLD, // ������ �ִ�
		AWAY // �� �� ����
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
		bool prevPush; // ���� �����ӿ� ���ȴ��� �ȴ��ȴ���..
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


