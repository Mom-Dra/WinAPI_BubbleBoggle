#include "AnimationObject.h"
#include "Core.h"
#include "Player.h"

namespace MomDra
{
	AnimationObject::AnimationObject() noexcept : Object{ Core::GetInstance().GetResolution() / 2.0f, Vector2::One * 20.0f }
	{
		CreateAnimator();

		GetAnimator()->LoadAnimation(L"\\animation\\Player_Destory.anim");
		GetAnimator()->Play(PlayerSetting::ROTATE_2, true);
	}

	void AnimationObject::Update() noexcept
	{

	}
}