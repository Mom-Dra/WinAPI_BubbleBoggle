#pragma once
#include "ImageObject.h"

namespace MomDra
{
	class Player : public ImageObject
	{
	public:
		explicit Player(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath);

		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;
	};
}
