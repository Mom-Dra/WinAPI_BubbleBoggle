#pragma once
#include "Object.h"

namespace MomDra
{
	class Projectile : public Object
	{
	private:

	public:
		explicit Projectile(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::PROJECTILE);
		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		virtual void OnCollisionEnter(const Collider* other);

		inline virtual std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<Projectile>(*this);
		}
	};


	class ProjectileState
	{
	public:
		static ProjectileState aa;


	public:
		//static inline ProjectileState& GetInstance() noexcept
		virtual void OnCollisionEnter(const Collider* other) = 0;

	private:
		explicit ProjectileState() noexcept = default;
		explicit ProjectileState(const ProjectileState& other) = delete;
		ProjectileState& operator=(const ProjectileState& other) = delete;
	};

	class ProjectileAttackState
	{
	public:
		
	};

}
