#pragma once
#include "Object.h"
#include <set>
#include "Vector2.h"
#include <iostream>

using namespace CK;

namespace MomDra
{
	class TileRectangle : public Object
	{
	public:
		struct TileInfo
		{
			Vector2 pos;
			Vector2 scale;
			bool isWall;

			bool operator==(const TileInfo& other)
			{
				return pos == other.pos && scale == other.scale;
			}

			friend std::ostream& operator<<(std::ostream& os, const TileInfo& tile)
			{
				os << "Position: " << tile.pos << ", Scale: " << tile.scale << ", IsWall: " << tile.isWall;
				return os;
			}
		};

		using TileVec = std::vector<TileInfo>;

	// 타일을 관리하는 Vector도 같이 관리하자, 분리하는게 좋을 듯
	private:
		static inline TileVec tileVec;

	public:
		static constexpr inline int TILE_SIZE_X{ 20 };
		static constexpr inline int TILE_SIZE_Y{ 20 };
		static constexpr inline Vector2 TILE_SIZE{ TILE_SIZE_X, TILE_SIZE_Y };

	public:
		explicit TileRectangle(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept;

		static inline const TileVec& GetTileVec() noexcept
		{
			return tileVec;
		}

		static inline void AddTile(const Vector2& pos, const Vector2& scale)
		{
			tileVec.emplace_back(pos, scale);
		}
		static inline void AddTile(const TileInfo& tileInfo)
		{
 			tileVec.emplace_back(tileInfo);
		}

		static inline void RemoveTile(const TileInfo& tileInfo)
		{
			auto end{ std::remove(tileVec.begin(), tileVec.end(), tileInfo) };
			tileVec.erase(end, tileVec.end());
		}

		static inline Vector2 GetRealTilePos(unsigned int xPos, unsigned int yPos)
		{
			return Vector2{ (xPos + 0.5f) * TILE_SIZE_X, (yPos + 0.5f) * TILE_SIZE_Y };
		}

		static inline Vector2 GetRealTilePos(float xPos, float yPos)
		{
			return Vector2{ (xPos + 0.5f) * TILE_SIZE_X, (yPos + 0.5f) * TILE_SIZE_Y };
		}

		static inline Vector2 GetRealTilePos(const Vector2& pos)
		{
			return Vector2{ (pos.X + 0.5f) * TILE_SIZE_X, (pos.Y + 0.5f) * TILE_SIZE_Y };
		}

		static void SaveFile(std::wofstream& out);
		static void LoadFile(std::wifstream& in);

		void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		inline std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<TileRectangle>(*this);
		}
	};
}
