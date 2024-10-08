#include "Animation.h"
#include "Object.h"

namespace MomDra
{
	Animation::Animation(const std::wstring& name, Animator* animator) noexcept : name{ name }, animator{ animator }, currFrame{ 0 }, time{ 0.0f }
	{

	}

	void Animation::Update() noexcept
	{
		time += TimeManager::GetInstance().GetDeltaTime();

		if (time > frames[currFrame].duration)
		{
			time = 0.0f;
			currFrame = (currFrame + 1) % frames.size();
		}
	}

	void Animation::Render(const HDC& hdc) const noexcept
	{
		Object* owner{ animator->GetOwner() };
		Vector2 pos{ owner->GetPos() };
		
		const Vector2 slice{ frames[currFrame].slice };
		const Vector2 leftTop{ frames[currFrame].leftTop };

		TransparentBlt(hdc, pos.X - slice.X / 2.0f, pos.Y - slice.Y / 2.0f, slice.X, slice.Y, texture->GetDC(), leftTop.X, leftTop.Y, slice.X, slice.Y, RGB(255, 255, 255));
	}

	void Animation::Create(std::shared_ptr<Texture> texture, const Vector2& leftTop, const Vector2& sliceSize, const Vector2& step, float duration, unsigned int frameCount)
	{
		this->texture = texture;

		for (unsigned int i{ 0 }; i < frameCount; ++i)
		{
			AnimationFrame frame;
			frame.duration = duration;
			frame.slice = sliceSize;
			frame.leftTop = leftTop + step * i;

			frames.emplace_back(frame);
		}
	}
}
