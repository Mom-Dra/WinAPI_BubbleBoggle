#pragma once
#include "framework.h"
#include "Animation.h"
#include <unordered_map>
#include <string>
#include <memory>
#include "Texture.h"
#include "Vector2.h"

using namespace CK;

namespace MomDra
{
	class Object;

	class Animator
	{
	private:
		std::unordered_map<std::wstring, std::unique_ptr<Animation>> animationMap;
		Animation* currAnimation;
		Object* owner;
		bool repeat;

	public:
		explicit Animator(Object* owner) noexcept;
		explicit Animator(const Animator& other) noexcept;
		Animator& operator=(const Animator& other) noexcept = delete;

		inline Object* GetOwner() const noexcept { return owner; }
		inline void SetOwner(Object* owner) noexcept { this->owner = owner; }

		void Update() const noexcept;
		void Render(const HDC& hdc) const noexcept;

		Animation* FindAnimation(const std::wstring& animationName) const noexcept;
		void CreateAnimation(const std::wstring& animationName, std::shared_ptr<Texture> texture, const Vector2& leftTop, const Vector2& sliceSize, const Vector2& step, float duration, unsigned int frameCount);
		void Play(const std::wstring& animationName, bool repeat) noexcept;
	};
}