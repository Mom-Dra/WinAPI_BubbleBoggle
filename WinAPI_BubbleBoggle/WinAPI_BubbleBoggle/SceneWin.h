#pragma once
#include "Scene.h"

namespace MomDra
{
	class SceneWin : public Scene
	{
	private:
		static constexpr inline float GAME_WIN_BGM_LENGTH{ 5.0f };
		float time{ 0.0f };

	public:
		explicit SceneWin() noexcept = default;
		explicit SceneWin(const std::wstring& name) noexcept : Scene{ name } {}

		virtual void Enter() noexcept override;
		virtual void Update() noexcept override;
		inline virtual void Exit() noexcept override { time = 0.0f; }
	};
}
