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
		explicit SceneTool(const std::wstring& name) noexcept : Scene{ name } {}

		virtual void Update() const noexcept override;
		virtual void Enter() noexcept override;
		virtual void Exit() noexcept override;

		void SetTileIndex() const noexcept;
	};
}
