#pragma once
#include "Object.h"
#include "AI.h"

namespace MomDra
{
	class Monster : public Object
	{
	private:
		//std::unique_ptr<AI> ai;

	public:
		explicit Monster(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::MONSTER);

		void Update() noexcept override;

		//inline void SetAI(std::unique_ptr<AI> ai) { this->ai = std::move(ai); }

		virtual void OnCollisionEnter(const Collider* other) override;

		virtual std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<Monster>(*this);
		}
	};
}
