#pragma once
#include "Object.h"
#include "Tag.h"
#include <vector>
#include <memory>
#include <array>
#include <string>

namespace MomDra
{
	class Scene
	{
	private:
		using Pair = std::pair<unsigned int, unsigned int>;

		std::array<std::vector<std::unique_ptr<Object>>, static_cast<int>(Layer::LAST)> objects;
		std::wstring sceneName;

		Pair tileXY;

	public:
		explicit Scene() noexcept = default;
		explicit Scene(const std::wstring& name) noexcept;

		virtual ~Scene() noexcept = default;

		inline const std::wstring& GetName() const noexcept { return sceneName; }
		inline const Pair& GetTileXY() const noexcept { return tileXY; }

		inline void SetName(const std::wstring& sceneName) noexcept { this->sceneName = sceneName; }

		virtual void Enter() noexcept = 0;
		virtual void Exit() noexcept = 0;

		virtual void Update() noexcept;
		void LateUpdate() const noexcept;
		void Render(const HDC& hdc) noexcept;

		inline const std::vector<std::unique_ptr<Object>>& GetLayerObject(const Layer& layer) const noexcept { return objects[static_cast<int>(layer)]; }
		inline std::vector<std::unique_ptr<Object>>& GetUILayerObject() noexcept { return objects[static_cast<int>(Layer::UI)]; }
		inline void AddObject(std::unique_ptr<Object> obj) noexcept { objects[static_cast<int>(obj->GetLayer())].emplace_back(std::move(obj)); }
		inline void AddObject(Object* obj) noexcept { objects[static_cast<int>(obj->GetLayer())].emplace_back(obj); }
		inline void DeleteLayerObject(const Layer& layer) noexcept { objects[static_cast<int>(layer)].clear(); }
		inline void DeleteAllObject() noexcept { for (auto& objVec : objects) objVec.clear(); }

		void CreateTile(unsigned int xCount, unsigned int yCount);
		void LoadTile(const std::wstring& relativePath);
	};
}
