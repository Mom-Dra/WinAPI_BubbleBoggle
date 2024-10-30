#pragma once
#include <vector>

namespace MomDra
{
	class GameManager
	{
	private:
		int numOfMonster;
		int playerLife;

	public:
		static inline GameManager& GetInstance()
		{
			static GameManager instance;
			return instance;
		}

		inline void SetNumOfMonster(int numOfMonster) noexcept { this->numOfMonster = numOfMonster; }
		inline void SetPlayerLife(int playerLife) noexcept { this->playerLife = playerLife; }

		inline void DecreaseNumOfMonster() noexcept { --numOfMonster; if (numOfMonster == 0) GameWin(); }

		inline void GameOver() { EventManager::GetInstance().ChangeScene(SceneType::GAME_OVER); }
		inline void GameWin() {}

	private:
		explicit GameManager() noexcept = default;
		explicit GameManager(const GameManager& other) = delete;
		explicit GameManager(GameManager&& other) = delete;
		GameManager& operator=(const GameManager& other) = delete;
		GameManager& operator=(GameManager&& other) = delete;
	};
}
