#pragma once
#include "Scene.h"
#include <memory>
#include "UI.h"
#include <functional>

namespace MomDra
{
	class SceneTool : public Scene
	{
	private:
		UI* ui;

		using SCENE_BTN_FUNC = std::function<void(const Scene&)>;

	public:
		explicit SceneTool() noexcept = default;
		explicit SceneTool(const std::wstring& name) noexcept;

		virtual void Update() noexcept override;
		virtual void Enter() noexcept override;
		virtual void Exit() noexcept override;

		void SetTileIndex() const noexcept;
		void SaveTile(const std::wstring& path) const;
		void SaveTileData();
		void LoadTileData();
	};
}
