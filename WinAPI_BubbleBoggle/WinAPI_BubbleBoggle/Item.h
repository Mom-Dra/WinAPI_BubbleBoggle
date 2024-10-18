#pragma once
#include  "Object.h"

namespace MomDra
{
	class Item : public Object
	{
	private:
		static constexpr inline float speed{ 100.0f };
		static constexpr inline Vector2 itemScale{ 20.0f, 20.0f };
		static constexpr inline float canCollisionTime{ 2.0f };

		float time{ 0.0f };
		bool canCollision{ false };

	public:
		explicit Item(const Vector2& pos, const Vector2& scale = itemScale, const Layer& layer = Layer::Item) noexcept;

		virtual void Update() noexcept override;

		inline virtual void Render(const HDC& hdc) const noexcept override;

		virtual void OnCollisionEnter(const Collider* other) override;

		inline virtual std::unique_ptr<Object> Clone() const
		{
			return std::unique_ptr<Object>();
		}
	};
}
