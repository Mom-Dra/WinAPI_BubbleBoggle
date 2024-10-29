#pragma once

#include "Scene.h"

namespace MomDra
{
	class SceneStage1 : public Scene
	{
	private:

	public:
		explicit SceneStage1() noexcept = default;
		explicit SceneStage1(const std::wstring& name) noexcept : Scene{ name } {}

		virtual void Enter() noexcept override;
		virtual void Update() noexcept override;
		virtual void Exit() noexcept override;
	};
}
