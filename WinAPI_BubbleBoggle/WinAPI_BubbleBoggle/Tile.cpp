#include "Tile.h"
#include "Camera.h"

namespace MomDra
{
	Tile::Tile(const Vector2& pos, std::shared_ptr<Texture> texture, const Layer& layer) noexcept : Object{ pos, Vector2{TILE_SIZE, TILE_SIZE}, layer }, texture{ texture }, index{ 1 }
	{

	}

	void Tile::Update() noexcept
	{

	}

	void Tile::Render(const HDC& hdc) const noexcept
	{
		if (!texture) return;

		int width{ texture->GetWidth() };
		int height{ texture->GetHeight() };

		int maxCol{ width / TILE_SIZE };
		int maxRow{ height / TILE_SIZE };

		int curRow{ index / maxCol };
		int currCol{ index % maxCol };

		if (maxRow <= curRow)
			return;

		const Vector2& renderPos{ Camera::GetInstance().GetRenderPos(GetPos()) };
		const Vector2& scale{ GetScale() };

		BitBlt(hdc, renderPos.X, renderPos.Y, scale.X, scale.Y, texture->GetDC(), currCol * TILE_SIZE, curRow * TILE_SIZE, SRCCOPY);

		Object::Render(hdc);
	}
}
