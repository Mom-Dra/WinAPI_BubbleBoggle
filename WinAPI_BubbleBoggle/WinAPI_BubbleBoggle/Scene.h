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
		std::array<std::vector<std::unique_ptr<Object>>, static_cast<int>(Layer::LAST)> objects;
		std::wstring sceneName;

	public:
		explicit Scene() noexcept = default;
		explicit Scene(const std::wstring& name) noexcept : sceneName{ name } {}

		virtual ~Scene() noexcept = default;

		inline const std::wstring& GetName() { return sceneName; }
		inline void SetName(const std::wstring& sceneName) noexcept { this->sceneName = sceneName; }

		virtual void Enter() noexcept = 0;
		virtual void Exit() noexcept = 0;

		virtual void Update() const noexcept;
		void LateUpdate() const noexcept;
		void Render(const HDC& hdc) noexcept;

		inline const std::vector<std::unique_ptr<Object>>& GetLayerObject(const Layer& layer) const noexcept { return objects[static_cast<int>(layer)]; }
		inline void AddObject(Object* obj) noexcept { objects[static_cast<int>(obj->GetLayer())].emplace_back(obj); }
		inline void DeleteLayerObject(const Layer& layer) noexcept { objects[static_cast<int>(layer)].clear(); }
		inline void DeleteAllObject() noexcept { for (auto& objVec : objects) objVec.clear(); }
	};
}
