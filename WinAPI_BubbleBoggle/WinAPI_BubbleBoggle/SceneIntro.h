#pragma once

#include "Scene.h"

namespace MomDra
{
	class SceneIntro : public Scene
	{
	private:
		static constexpr inline float INTRO_TIME{ 8.0f };

		float time{ 0.0f };

	public:
		explicit SceneIntro() noexcept = default;
		explicit SceneIntro(const std::wstring& name) noexcept : Scene{ name } {}

		virtual void Enter() noexcept override;
		virtual void Update() noexcept override;
		virtual void Exit() noexcept override;
	};
}
