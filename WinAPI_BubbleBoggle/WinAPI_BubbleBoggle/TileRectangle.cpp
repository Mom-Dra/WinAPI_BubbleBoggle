#include "TileRectangle.h"
#include "Camera.h"
#include <fstream>
#include <iostream>

namespace MomDra
{
    TileRectangle::TileRectangle(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept : Object{ pos, scale, layer }
    {

    }

    void TileRectangle::SaveFile(std::wofstream& out)
    {
        unsigned int size{ static_cast<unsigned int>(tileVec.size()) };

        out << size << ' ';

        for (const TileInfo& tileInfo : tileVec)
        {
            out << tileInfo.pos.X << ' ' << tileInfo.pos.Y << ' ';
            out << tileInfo.scale.X << ' ' << tileInfo.scale.Y << '\n';

            std::cout << "Save Tile: " << tileInfo << std::endl;
        }
    }

    void TileRectangle::LoadFile(std::wifstream& in)
    {
        tileVec.clear();

        unsigned int size;

        in >> size;

        tileVec.reserve(size);

        for (unsigned int i{ 0 }; i < size; ++i)
        {
            TileInfo tileInfo;

            in >> tileInfo.pos.X >> tileInfo.pos.Y;
            in >> tileInfo.scale.X >> tileInfo.scale.Y;

            tileVec.emplace_back(tileInfo);

            std::cout << "Load Tile: " << tileInfo << std::endl;
        }
    }

    void TileRectangle::Update() noexcept
    {

    }

    void TileRectangle::Render(const HDC& hdc) const noexcept
    {
        const Vector2& renderPos{ Camera::GetInstance().GetRenderPos(GetPos()) };
        const Vector2& scale{ GetScale() };

        //BitBlt(hdc, static_cast<int>(renderPos.X), static_cast<int>(renderPos.Y), static_cast<int>(scale.X), static_cast<int>(scale.Y), texture->GetDC(), currCol * TILE_SIZE_X, curRow * TILE_SIZE_Y, SRCCOPY);
        Rectangle(hdc, static_cast<int>(renderPos.X - scale.X / 2.0f), static_cast<int>(renderPos.Y - scale.Y / 2.0f), static_cast<int>(renderPos.X + scale.X / 2.0f), static_cast<int>(renderPos.Y + scale.Y / 2.0f));
       
        Object::Render(hdc);
    }
}
