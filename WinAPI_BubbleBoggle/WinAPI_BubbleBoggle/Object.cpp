#include "Object.h"

namespace MomDra
{
	Object::Object(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept : pos{ pos }, scale{ scale }, isAlive{ true }, layer{ layer }
	{

	}

	void Object::LateUpdate() noexcept
	{
		if (collider)
			collider->LateUpdate();
	}

	void Object::Render(const HDC& hdc) const noexcept
	{
		ComponentRender(hdc);
	}

	void Object::ComponentRender(const HDC& hdc) const noexcept
	{
		if (collider)
			collider->Render(hdc);
	}

	Collider* Object::GetCollider() const noexcept
	{
		return collider.get();
	}

	void Object::CreateCollider(const Vector2& scale) noexcept
	{
		collider = std::make_unique<Collider>(this, scale);
	}
}
