#pragma once
#include "Tag.h"
#include <array>

namespace MomDra
{
	class CollisionManager
	{
	private:
		std::array<unsigned int, static_cast<int>(Layer::LAST)> checkArr;

	public:
		static CollisionManager& GetInstance() noexcept;

		void Initialize() noexcept;
		void Update() noexcept;
		void CheckGroup(const Layer& layer1, const Layer& layer2) noexcept;
		void Reset() noexcept;

	private:
		explicit CollisionManager() noexcept = default;
		explicit CollisionManager(const CollisionManager& other) noexcept = delete;
		CollisionManager& operator=(const CollisionManager& other) noexcept = delete;
	};
}
