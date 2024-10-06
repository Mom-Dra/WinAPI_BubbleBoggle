#pragma once
#include "Tag.h"
#include <array>
#include "Collider.h"
#include <unordered_map>

namespace MomDra
{
	union ColliderId
	{
		struct
		{
			unsigned int leftId;
			unsigned int rightId;
		};

		unsigned long long id;
	};

	class CollisionManager
	{
	private:
		std::array<unsigned int, static_cast<int>(Layer::LAST)> checkArr;
		std::unordered_map<unsigned long long, bool> ColliderInfoMap;
		
	public:
		static CollisionManager& GetInstance() noexcept;

		void Initialize() noexcept;
		void Update() noexcept;
		void CheckGroup(const Layer& layer1, const Layer& layer2) noexcept;
		void Reset() const noexcept;

	private:
		explicit CollisionManager() noexcept = default;
		explicit CollisionManager(const CollisionManager& other) noexcept = delete;
		CollisionManager& operator=(const CollisionManager& other) noexcept = delete;

		void CollisionGroupUpdate(const Layer& layer1, const Layer& layer2) noexcept;
		bool IsCollision(Collider* laye1Col, Collider* layer2Col) const noexcept;
	};
}
