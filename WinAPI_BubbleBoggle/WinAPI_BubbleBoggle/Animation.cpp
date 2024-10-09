#include "Animation.h"
#include "Object.h"
#include "Camera.h"

namespace MomDra
{
	Animation::Animation(const std::wstring& name, Animator* animator) noexcept : name{ name }, animator{ animator }, currFrame{ 0 }, time{ 0.0f }, isFinish{ false }
	{

	}

	void Animation::Update() noexcept
	{
		if (isFinish) return;

		time += TimeManager::GetInstance().GetDeltaTime();

		if (frames[currFrame].duration < time)
		{
			time = time - frames[currFrame].duration;

			++currFrame;

			if (frames.size() == currFrame)
			{
				currFrame = -1;
				time = 0.0f;
				isFinish = true;
			}
		}
	}

	void Animation::Render(const HDC& hdc) const noexcept
	{
		if (isFinish) return;

		Object* owner{ animator->GetOwner() };
		Vector2 pos{ owner->GetPos() };
		
		const Vector2 offSet{ frames[currFrame].offSet };
		const Vector2 slice{ frames[currFrame].slice };
		const Vector2 leftTop{ frames[currFrame].leftTop };

		pos += offSet; // Offset만큼 추가 위치 이동

		pos = Camera::GetInstance().GetRenderPos(pos);

		TransparentBlt(hdc, static_cast<int>(pos.X - slice.X / 2.0f), static_cast<int>(pos.Y - slice.Y / 2.0f), static_cast<int>(slice.X), static_cast<int>(slice.Y), texture->GetDC(), static_cast<int>(leftTop.X), static_cast<int>(leftTop.Y), static_cast<int>(slice.X), static_cast<int>(slice.Y), RGB(255, 255, 255));
	}

	void Animation::Create(std::shared_ptr<Texture> texture, const Vector2& leftTop, const Vector2& sliceSize, const Vector2& step, float duration, unsigned int frameCount)
	{
		this->texture = texture;

		for (unsigned int i{ 0 }; i < frameCount; ++i)
		{
			AnimationFrame frame;
			frame.duration = duration;
			frame.slice = sliceSize;
			frame.leftTop = leftTop + step * static_cast<float>(i);

			frames.emplace_back(frame);
		}
	}
}
