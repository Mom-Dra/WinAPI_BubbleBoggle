#pragma once
#include "Object.h"

namespace MomDra
{
	class Player : public Object
	{
	private:
		PlayerState currState;
		PlayerState prevState;

		int lookDir;
		bool isGround;

	public:
		explicit Player(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::PLAYER);

		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		inline bool IsGround() const noexcept { return isGround; }

		virtual void OnCollisionEnter(const Collider* other) override;
		virtual void OnCollisionStay(const Collider* other) override;
		virtual void OnCollisionExit(const Collider* other) override;

		inline virtual std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<Player>(*this);
		}

	private:
		void Attack() const noexcept;
		void Move();
		void Jump();

		void UpdateState();
		void UpdateAnimation();
	};
}