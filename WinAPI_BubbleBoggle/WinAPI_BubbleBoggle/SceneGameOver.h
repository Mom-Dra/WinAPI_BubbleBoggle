#pragma once
#include "Scene.h"

namespace MomDra
{
	class SceneGameOver : public Scene
	{
	private:
		static constexpr inline float GAME_OVER_BGM_LENGTH{ 2.5f };
		float time{ 0.0f };

	public:
		explicit SceneGameOver() noexcept = default;
		explicit SceneGameOver(const std::wstring& name) noexcept : Scene{ name } {}

		virtual void Enter() noexcept override;
		virtual void Update() noexcept override;
		virtual void Exit() noexcept override;
	};
}
