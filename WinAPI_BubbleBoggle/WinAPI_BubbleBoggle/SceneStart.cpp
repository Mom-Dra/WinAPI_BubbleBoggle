#include "SceneStart.h"
#include "Player.h"
#include "Monster.h"
#include "Texture.h"
#include "PathManager.h"
#include "CollisionManager.h"

namespace MomDra
{	
	void SceneStart::Enter() noexcept
	{
		std::wstring filePath{ PathManager::GetContentPath() };
		filePath.append(L"\\texture\\player.bmp");

		AddObject(new Player{ Vector2{640.0f, 384.0f}, Vector2{100.0f, 100.0f}, filePath }, Layer::PLAYER);
		AddObject(new Monster{ Vector2{200.0f, 200.0f}, Vector2{100.0f, 100.0f}, filePath }, Layer::MONSTER);

		// 충돌 지정
		CollisionManager::GetInstance().CheckGroup(Layer::PLAYER, Layer::MONSTER);
	}

	void SceneStart::Exit() noexcept
	{
		CollisionManager::GetInstance().Reset();
	}
}
