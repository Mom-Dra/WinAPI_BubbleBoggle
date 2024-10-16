#pragma once
#include "Object.h"

namespace MomDra
{
	class Ground : public Object
	{
	private:


	public:
		explicit Ground(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::GROUND);

		virtual void OnCollisionEnter(const Collider* other) override;
		virtual void OnCollisionStay(const Collider* other) override;
		virtual void OnCollisionExit(const Collider* other) override;

	private:
		virtual void Start() override;
		virtual void Update() noexcept override;

		inline virtual std::unique_ptr<Object> Clone() const { return std::make_unique<Ground>(*this); }
	};
}
