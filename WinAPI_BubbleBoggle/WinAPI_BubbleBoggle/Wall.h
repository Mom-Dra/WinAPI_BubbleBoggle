#pragma once
#include "Object.h"

namespace MomDra
{
	class Wall : public Object
	{
	private:

	public:
		explicit Wall(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::Ground);

		virtual void OnCollisionStay(const Collider* other) override;

	private:
		void Update() noexcept override;

		inline virtual std::unique_ptr<Object> Clone() const override { return std::make_unique<Wall>(*this); }
	};
}
