#include "KeyManager.h"
#include "framework.h"
#include "Core.h"

namespace MomDra
{
	std::array<int, static_cast<int>(Key::LAST)> KeyManager::keyArr
	{
		VK_LEFT,
		VK_RIGHT,
		VK_UP,
		VK_DOWN,

		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',' N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

		VK_MENU,
		VK_CONTROL,
		VK_LSHIFT,
		VK_SPACE,
		VK_RETURN,
		VK_ESCAPE
	};

	KeyManager& KeyManager::GetInstance() noexcept
	{
		static KeyManager instance;

		return instance;
	}

	void KeyManager::Initialize() noexcept
	{
		for (int i = 0; i < static_cast<int> (Key::LAST); ++i)
		{
			keyStates[i].state = KeyState::NONE;
			keyStates[i].prevPush = false;
		}
	}

	void KeyManager::Update() noexcept
	{
		// 윈도우 포커싱 알아내기
		//HWND hMainWnd{ Core::GetInstance().GetHwnd() };
		HWND hWnd = GetFocus();

		// 윈도우가 포커싱일 때
		if (hWnd != nullptr)
		{
			for (int i = 0; i < static_cast<int>(Key::LAST); ++i)
			{
				if (GetAsyncKeyState(keyArr[i]) & 0x8000)
				{
					if (keyStates[i].prevPush)
					{
						keyStates[i].state = KeyState::HOLD;
					}
					else
					{
						keyStates[i].state = KeyState::TAP;
					}

					keyStates[i].prevPush = true;
				}
				else
				{
					if (keyStates[i].prevPush)
					{
						keyStates[i].state = KeyState::AWAY;
					}
					else
					{
						keyStates[i].state = KeyState::NONE;
					}

					keyStates[i].prevPush = false;
				}
			}
		}
		else
		{
			for (int i = 0; i < static_cast<int>(Key::LAST); ++i)
			{
				keyStates[i].prevPush = false;
				
				KeyState keyState{ keyStates[i].state };

				if (keyState == KeyState::TAP || keyState == KeyState::HOLD)
					keyStates[i].state = KeyState::AWAY;
				else if (keyState == KeyState::AWAY)
					keyStates[i].state = KeyState::NONE;
			}
		}
	}
}