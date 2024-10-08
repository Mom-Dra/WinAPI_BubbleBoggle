#include "Object.h"

namespace MomDra
{
	Object::Object(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept : pos{ pos }, scale{ scale }, isAlive{ true }, layer{ layer }
	{

	}

	Object::Object(const Object& other) noexcept : pos{ other.pos }, scale{ other.scale }, isAlive{ true }, layer{ other.layer }
	{
		if (other.collider)
		{
			collider = std::make_unique<Collider>(*other.collider);
			collider->SetOwner(this);
		}
		
		if (other.animator)
		{
			animator = std::make_unique<Animator>(*other.animator);
			animator->SetOwner(this);
		}
	}

	void Object::LateUpdate() noexcept
	{
		if (collider)
			collider->LateUpdate();

		// Update 위치 여기??
		if (animator)
			animator->Update();
	}

	void Object::Render(const HDC& hdc) const noexcept
	{
		ComponentRender(hdc);
	}

	void Object::ComponentRender(const HDC& hdc) const noexcept
	{
		if (collider)
			collider->Render(hdc);

		if (animator)
			animator->Render(hdc);
	}
}
