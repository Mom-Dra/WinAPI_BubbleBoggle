#pragma once
#include "Object.h"
#include <set>

namespace MomDra
{
	class TileRectangle : public Object
	{
	private:
		using TileSet = std::set<std::pair<unsigned int, unsigned int>>;

		static inline TileSet tileSet;

	public:
		static constexpr inline int TILE_SIZE_X{ 20 };
		static constexpr inline int TILE_SIZE_Y{ 20 };

	public:
		explicit TileRectangle(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept;

		static inline const TileSet& GetTileSet() noexcept
		{
			return tileSet;
		}

		static inline bool CanAdd(unsigned int xPos, unsigned int yPos)
		{
			return tileSet.find(std::make_pair(xPos, yPos)) == tileSet.end();
		}

		static inline void AddTile(unsigned int xPos, unsigned int yPos)
		{
			if (CanAdd(xPos, yPos))
				tileSet.emplace(xPos, yPos);
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
