#pragma once
#include "Texture.h"
#include "Object.h"
#include "ImageObject.h"

namespace MomDra
{
	class Item : public ImageObject
	{
	private:
		static constexpr inline float SPEED{ 100.0f };
		static constexpr inline Vector2 ITEM_SCALE{ 30.0f, 30.0f };
		static constexpr inline float CAN_COLLISION_TIME{ 2.0f };
		static constexpr inline float DESTROY_ANIM_TIME{ 10.0f };
		static constexpr inline float DESTROY_TIME{ 1.0f };

		float time{ 0.0f };
		bool canCollision{ false };
		bool isDestroy{ false };

	public:
		explicit Item(const Vector2& pos, const std::wstring& imgPath, const Vector2& scale = ITEM_SCALE, const Layer& layer = Layer::Item) noexcept;

		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		virtual void OnCollisionEnter(const Collider* other) override;
		virtual void OnCollisionStay(const Collider* other) override;

		inline virtual std::unique_ptr<Object> Clone() const
		{
			return std::unique_ptr<Object>();
		}

	private:
		void DestroyItem();
	};
}
