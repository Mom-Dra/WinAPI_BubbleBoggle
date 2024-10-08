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

	struct AnimationFrame
	{
		Vector2 leftTop;
		Vector2 slice;
		float duration;
	};

	class Animation
	{
	private:
		std::wstring name;
		Animator* animator;
		std::shared_ptr<Texture> texture;
		std::vector<AnimationFrame> frames;
		unsigned int currFrame;
		float time;

	public:
		explicit Animation(const std::wstring& name, Animator* animator) noexcept;

		void Update() noexcept;
		void Render(const HDC& hdc) const noexcept;

		void Create(std::shared_ptr<Texture> texture, const Vector2& leftTop, const Vector2& sliceSize, const Vector2& step, float duration ,unsigned int frameCount);

		inline const std::wstring& GetName() const noexcept { return name; }

	private:
		inline void SetName(const std::wstring& name) noexcept { this->name = name; }

		friend class Animator;
	};
}
