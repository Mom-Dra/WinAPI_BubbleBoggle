#pragma once
#include "Object.h"

namespace MomDra
{
	class Projectile : public Object
	{
	private:

	public:
		explicit Projectile(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::DEFAULT);
		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		virtual void OnCollisionEnter(const Collider* other);
	};
}
