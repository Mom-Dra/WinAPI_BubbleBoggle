#include "AnimationObject.h"
#include "Core.h"
#include "Player.h"

namespace MomDra
{
	AnimationObject::AnimationObject() noexcept : Object{ Core::GetInstance().GetResolution() / 2.0f, Vector2::One * 20.0f, Layer::Default }
	{
		CreateAnimator();
	}

	void AnimationObject::Update() noexcept
	{

	}
}