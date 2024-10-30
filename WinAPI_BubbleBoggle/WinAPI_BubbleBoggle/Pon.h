#pragma once
#include "Object.h"
#include "Vector2.h"

using namespace CK;

namespace MomDra
{
	class Pon : public Object
	{
	private:
		static constexpr inline float duration{ 1.0f };

		float time{ 0.0f };

	public:
		explicit Pon(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::DEFAULT) noexcept;

		void Update() noexcept override;

		inline std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<Pon>(*this);
		}
	};
}
