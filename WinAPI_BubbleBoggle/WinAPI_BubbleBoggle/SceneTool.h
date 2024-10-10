#pragma once
#include "Scene.h"

namespace MomDra
{
	class SceneTool : public Scene
	{
	public:
		explicit SceneTool() noexcept = default;
		explicit SceneTool(const std::wstring& name) noexcept : Scene{ name } {}

		virtual void Update() const noexcept override;
		virtual void Enter() noexcept override;
		virtual void Exit() noexcept override;

		void SetTileIndex() const noexcept;
	};
}
