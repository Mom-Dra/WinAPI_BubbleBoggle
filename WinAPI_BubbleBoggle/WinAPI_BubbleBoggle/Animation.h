#pragma once
#include "framework.h"
#include <string>
#include <memory>
#include <vector>
#include "Vector2.h"
#include "Texture.h"
#include "TimeManager.h"

using namespace CK;

namespace MomDra
{
	class Animator;

	// 일반적으로 플레이어의 위치가, 이미지의 발쪽에 잡아준다!

	struct AnimationFrame
	{
		Vector2 leftTop;
		Vector2 slice;
		Vector2 offSet;
		float duration;
	};

	class Animation
	{
	private:
		std::wstring name;
		Animator* animator;
		std::shared_ptr<Texture> texture;
		std::vector<AnimationFrame> frames;
		int currFrame;
		float time;
		bool isFinish;

	public:
		explicit Animation(const std::wstring& name, Animator* animator) noexcept;

		void Update() noexcept;
		void Render(const HDC& hdc) const noexcept;

		void Create(std::shared_ptr<Texture> texture, const Vector2& leftTop, const Vector2& sliceSize, const Vector2& step, float duration ,unsigned int frameCount);

		inline const std::wstring& GetName() const noexcept { return name; }
		inline bool IsFinish() const noexcept { return isFinish; }
		inline AnimationFrame& GetFrame(int frameIndex) noexcept { return frames[frameIndex]; }
		inline int GetMaxFrame() const noexcept { return frames.size(); }
		inline void SetFrame(int frameIndex) noexcept { isFinish = false; currFrame = frameIndex; time = 0.0f; }

	private:
		inline void SetName(const std::wstring& name) noexcept { this->name = name; }

		friend class Animator;
	};
}
