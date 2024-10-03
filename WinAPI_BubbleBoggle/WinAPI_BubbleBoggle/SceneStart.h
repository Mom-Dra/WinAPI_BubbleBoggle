#pragma once
#include "Scene.h"

namespace MomDra
{
	class SceneStart : public Scene
	{
	private:


	public:

		virtual void Enter() noexcept override;
		virtual void Exit() noexcept override;
	};
}
