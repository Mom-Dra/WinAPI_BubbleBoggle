#pragma once
#include "Object.h"

namespace MomDra
{
	class Monster : public Object
	{
	private:


	public:
		explicit Monster(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::MONSTER);

		virtual void OnCollisionEnter(const Collider* other) override;

		void Update() noexcept override;


		virtual std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<Monster>(*this);
		}
	};
}
