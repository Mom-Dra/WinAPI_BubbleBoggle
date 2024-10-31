#pragma once
#include "Score.h"
#include "ImageObject.h"

namespace MomDra
{
	class Score : public ImageObject
	{
	private:
		static constexpr inline Vector2 SCORE_SCALE{ 30.0f, 30.0f };
		static constexpr inline float MOVE_TIME{ 2.0f };
		static constexpr inline float SPEED{ 30.0f };

		float time{ 0.0f };

	public:
		inline explicit Score(const Vector2& pos, const std::wstring& imgPath, const Vector2& scale = SCORE_SCALE, const Layer& layer = Layer::Item) noexcept : ImageObject{ pos, scale, imgPath ,layer } {}

		virtual void Update() noexcept override;
	};
}
