#include "SceneStart.h"
#include "Player.h"
#include "ImageCache.h"
#include "Texture.h"
#include "PathManager.h"

namespace MomDra
{	
	void SceneStart::Enter() noexcept
	{
		AddObject(new Player{ Vector2{640.0f, 384.0f}, Vector2{100.0f, 100.0f}, ImageCache::playerImgPath }, Tag::PLAYER);
		
		Texture tex;

		std::wstring filePath{ PathManager::GetInstance().GetContentPath() };

		filePath.append(L"\\texture\\player.bmp");
		tex.Load(filePath);
	}

	void SceneStart::Exit() noexcept
	{

	}
}
