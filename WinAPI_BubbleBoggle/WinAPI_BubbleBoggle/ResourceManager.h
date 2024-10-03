#pragma once

#include "TimeManager.h"

namespace MomDra
{
	class ResourceManager
	{
	private:


	public:
		const ResourceManager& GetInstance() noexcept;



	private:
		explicit ResourceManager() noexcept = default;
		explicit ResourceManager(const ResourceManager& other) noexcept = delete;
		ResourceManager& operator=(const ResourceManager& other) noexcept = delete;
	}
}
