#pragma once

#include "TimeManager.h"
#include <unordered_map>
#include <string>
#include <memory>
#include "Texture.h"
#include "Sound.h"

namespace MomDra
{
	class ResourceManager
	{
	private:
		std::unordered_map<std::wstring, std::shared_ptr<Res>> textureMap;
		std::unordered_map<std::wstring, std::shared_ptr<Res>> soundMap;

	public:
		static ResourceManager& GetInstance() noexcept;

		std::shared_ptr<Texture> LoadTexture(const std::wstring& filePath);
		std::shared_ptr<Sound> LoadSound(const std::wstring& filePath);

		std::shared_ptr<Sound> FindSound(const std::wstring& filePath);

	private:
		explicit ResourceManager() noexcept = default;
		explicit ResourceManager(const ResourceManager& other) noexcept = delete;
		explicit ResourceManager(ResourceManager&& other) noexcept = delete;
		ResourceManager& operator=(const ResourceManager& other) noexcept = delete;
		ResourceManager& operator=(ResourceManager&& other) noexcept = delete;
	};
}
