#pragma once
#include "ImageObject.h"

namespace MomDra
{
	class Monster : public ImageObject
	{
	private:


	public:
		explicit Monster(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath, const Layer& layer = Layer::DEFAULT);

		virtual void OnCollisionEnter(const Collider* other) override;
	};
}
