#include "ResourceManager.h"
#include "PathManager.h"

namespace MomDra
{
	ResourceManager& ResourceManager::GetInstance() noexcept
	{
		static ResourceManager instance;

		return instance;
	}

	std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::wstring& filePath)
	{
		auto it{ textureMap.find(filePath) };

		if (it == textureMap.end())
		{
			std::shared_ptr<Texture> texture{ std::make_shared<Texture>(filePath) };
			textureMap.emplace(filePath, texture);
		}
		
		return std::dynamic_pointer_cast<Texture>(textureMap[filePath]);
	}
}
