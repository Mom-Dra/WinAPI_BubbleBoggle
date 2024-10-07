#pragma once
#include "Scene.h"

namespace MomDra
{
	class SceneStart : public Scene
	{
	private:


	public:
		explicit SceneStart() noexcept = default;
		explicit SceneStart(const std::wstring& name) noexcept : Scene{ name } {}

		virtual void Enter() noexcept override;
		virtual void Update() const noexcept;
		virtual void Exit() noexcept override;
	};
}
