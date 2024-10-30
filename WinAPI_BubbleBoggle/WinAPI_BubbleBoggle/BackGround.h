#pragma once
#include "Object.h"

namespace MomDra
{
	class BackGround : public Object
	{
	public:
		inline explicit BackGround() noexcept : Object{ Vector2::Zero, Vector2::Zero, Layer::DEFAULT } {}


	private:
		inline void Update() noexcept override {}
		virtual void Render(const HDC& hdc) const noexcept;

		inline std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<BackGround>(*this);
		}
	};
}
