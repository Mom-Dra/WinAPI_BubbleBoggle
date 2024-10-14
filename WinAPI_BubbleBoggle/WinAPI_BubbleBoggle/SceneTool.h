#pragma once
#include "Scene.h"
#include <memory>
#include "UI.h"

namespace MomDra
{
	class SceneTool : public Scene
	{
	private:
		UI* ui;

	public:
		explicit SceneTool() noexcept = default;
		explicit SceneTool(const std::wstring& name) noexcept;

		virtual void Update() noexcept override;
		virtual void Enter() noexcept override;
		virtual void Exit() noexcept override;

		void SetTileIndex() const noexcept;
		void SaveTile(const std::wstring& relativePath) const;
		void SaveTileData();
	};
}
