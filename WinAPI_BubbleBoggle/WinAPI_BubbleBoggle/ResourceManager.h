#pragma once

#include "TimeManager.h"
#include <unordered_map>
#include <string>
#include <memory>
#include "Texture.h"

namespace MomDra
{
	class ResourceManager
	{
	private:
		std::unordered_map<std::wstring, std::shared_ptr<Texture>> textureMap;

	public:
		static ResourceManager& GetInstance() noexcept;

		std::shared_ptr<Texture> LoadTexture(const std::wstring& filePath);

	private:
		explicit ResourceManager() noexcept = default;
		explicit ResourceManager(const ResourceManager& other) noexcept = delete;
		ResourceManager& operator=(const ResourceManager& other) noexcept = delete;
	};
}
