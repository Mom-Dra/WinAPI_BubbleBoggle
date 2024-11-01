#pragma once
#include "EventManager.h"
#include "SceneManager.h"

namespace MomDra
{
	class GameManager
	{
	private:
		static constexpr inline float HURRY_UP_TIME{ 30.0f };

		int numOfMonster;
		int playerLife;

		float time{ 0.0f };

	public:
		static inline GameManager& GetInstance()
		{
			static GameManager instance;
			return instance;
		}

		inline void SetNumOfMonster(int numOfMonster) noexcept { this->numOfMonster = numOfMonster; }
		inline void SetPlayerLife(int playerLife) noexcept { this->playerLife = playerLife; }
		inline void SetTime(float time) noexcept { this->time = time; }

		void Update();
	
		inline void DecreaseNumOfMonster() noexcept
		{
			--numOfMonster;
			if (numOfMonster == 0) GameWin();
		}

		inline void DecreasePlayerLife() noexcept
		{
			--playerLife;
			if (playerLife == 0)
			{
				GameOver();
				return;
			}

			SceneManager::GetInstance().GetCurrentScene()->GetUILayerObject().pop_back();
		}

		inline void GameOver() { EventManager::GetInstance().ChangeScene(SceneType::GameOver); }
		inline void GameWin() { EventManager::GetInstance().ChangeScene(SceneType::GameWin); }

	private:
		explicit GameManager() noexcept = default;
		explicit GameManager(const GameManager& other) = delete;
		explicit GameManager(GameManager&& other) = delete;
		GameManager& operator=(const GameManager& other) = delete;
		GameManager& operator=(GameManager&& other) = delete;

		void HurryUp();
	};
}
