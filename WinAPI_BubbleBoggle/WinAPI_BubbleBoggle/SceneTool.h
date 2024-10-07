#pragma once
#include "Scene.h"

namespace MomDra
{
	class SceneTool : public Scene
	{
	public:
		virtual void Enter() noexcept override;
		virtual void Exit() noexcept override;
	};
}
