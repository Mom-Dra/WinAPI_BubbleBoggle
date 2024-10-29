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

	std::shared_ptr<Sound> ResourceManager::LoadSound(const std::wstring& filePath)
	{
		auto it{ soundMap.find(filePath) };

		if (it == soundMap.end())
		{
			std::shared_ptr<Sound> sound{ std::make_shared<Sound>(filePath) };
			soundMap.emplace(filePath, sound);
		}

		return std::dynamic_pointer_cast<Sound>(soundMap[filePath]);
	}

	std::shared_ptr<Sound> ResourceManager::FindSound(const std::wstring& filePath)
	{
		auto it{ soundMap.find(filePath) };
		
		if (it == soundMap.end())
		{
			return nullptr;
		}

		return std::dynamic_pointer_cast<Sound>(it->second);
	}
}
