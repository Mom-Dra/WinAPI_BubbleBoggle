#pragma once

#include <memory>
#include "Object.h"

namespace MomDra
{
	class Tile : public Object
	{
	public:
		static constexpr inline int TILE_SIZE{ 16 };

	private:
		std::shared_ptr<Texture> texture;
		int imgIndex;

	public:
		explicit Tile(const Vector2& pos, std::shared_ptr<Texture> texture, const Layer& layer) noexcept;

		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		inline void SetTexture(std::shared_ptr<Texture> texture) noexcept { this->texture = texture; }
		inline void AddImgIndex() noexcept { ++imgIndex; }

		inline virtual std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<Tile>(*this);
		}
	};
}
