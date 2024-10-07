#pragma once
#include "ImageObject.h"

namespace MomDra
{
	class Monster : public ImageObject
	{
	private:

	public:
		explicit Monster(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath);
	};
}
