#pragma once
#include "ImageObject.h"

namespace MomDra
{
	class Projectile : public ImageObject
	{
	private:
		

	public:
		explicit Projectile(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath, const Layer& layer = Layer::DEFAULT);
		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		virtual void OnCollisionEnter(const Collider* other);
	};
}
