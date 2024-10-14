#include "Tile.h"
#include "Camera.h"
#include <fstream>

namespace MomDra
{
	Tile::Tile(const Vector2& pos, std::shared_ptr<Texture> texture, const Layer& layer) noexcept : Object{ pos, Vector2{TILE_SIZE, TILE_SIZE}, layer }, texture{ texture }, imgIndex{ 0 }
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

		int curRow{ imgIndex / maxCol };
		int currCol{ imgIndex % maxCol };

		if (maxRow <= curRow)
			return;

		const Vector2& renderPos{ Camera::GetInstance().GetRenderPos(GetPos()) };
		const Vector2& scale{ GetScale() };

		BitBlt(hdc, static_cast<int>(renderPos.X), static_cast<int>(renderPos.Y), static_cast<int>(scale.X), static_cast<int>(scale.Y), texture->GetDC(), currCol * TILE_SIZE, curRow * TILE_SIZE, SRCCOPY);

		Object::Render(hdc);
	}

	void Tile::SaveFile(std::wostream& wOut)
	{
		wOut << imgIndex << ' ';
	}

	void Tile::LoadFile(std::wifstream& wIn)
	{
		wIn >> imgIndex;
	}
}
