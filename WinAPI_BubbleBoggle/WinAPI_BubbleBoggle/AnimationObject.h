#pragma once
#include "Object.h"

namespace MomDra
{
	class AnimationObject : public Object
	{

	public:
		explicit AnimationObject() noexcept;

		void Update() noexcept override;

		inline virtual std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<AnimationObject>();
		}
	};
}
