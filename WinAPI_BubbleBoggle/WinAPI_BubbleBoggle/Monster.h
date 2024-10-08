#pragma once
#include "Object.h"

namespace MomDra
{
	class Monster : public Object
	{
	private:


	public:
		explicit Monster(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::DEFAULT);

		virtual void OnCollisionEnter(const Collider* other) override;

		void Update() noexcept override;
	};
}
