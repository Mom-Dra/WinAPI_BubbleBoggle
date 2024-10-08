#include "Animator.h"

namespace MomDra
{
	Animator::Animator(Object* owner) noexcept : currAnimation{ nullptr }, owner{ owner }
	{

	}

	Animator::Animator(const Animator& other) noexcept : currAnimation{ nullptr }, owner{ nullptr }
	{
		// unorderd_map은 어떻게 복사하나요?

	}

	void Animator::Update() const noexcept
	{
		if (currAnimation)
			currAnimation->Update();
	}

	void Animator::Render(const HDC& hdc) const noexcept
	{
		if (currAnimation)
			currAnimation->Render(hdc);
	}

	Animation* Animator::FindAnimation(const std::wstring& animationName) const noexcept
	{
		auto it{ animationMap.find(animationName) };

		if (it != animationMap.end()) return animationMap.at(animationName).get();

		return nullptr;
	}

	void Animator::CreateAnimation(const std::wstring& animationName, std::shared_ptr<Texture> texture, const Vector2& leftTop, const Vector2& sliceSize, const Vector2& step, float duration, unsigned int frameCount) noexcept
	{
		if (FindAnimation(animationName) != nullptr)
			throw std::runtime_error{ "Duplicate key error: Animation already exists." };

		std::unique_ptr<Animation> animation{ std::make_unique<Animation>(animationName, this) };

		animation->Create(texture, leftTop, sliceSize, step, duration, frameCount);

		animationMap.emplace(animationName, std::move(animation));
	}

	void Animator::Play(const std::wstring& animationName) noexcept
	{
		currAnimation = FindAnimation(animationName);
	}
}