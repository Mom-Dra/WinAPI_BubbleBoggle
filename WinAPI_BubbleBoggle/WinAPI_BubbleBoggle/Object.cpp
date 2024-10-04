#include "Object.h"

namespace MomDra
{
	Object::Object(const Vector2& pos, const Vector2& scale) noexcept : pos{ pos }, scale{ scale }
	{

	}

	void Object::SetPos(Vector2 pos) noexcept
	{
		this->pos = pos;
	}

	void Object::SetScale(Vector2 scale) noexcept
	{
		this->scale = scale;
	}

	const Vector2& Object::GetPos() const noexcept
	{
		return pos;
	}

	const Vector2& Object::GetScale() const noexcept
	{
		return scale;
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

	void Object::CreateCollider() noexcept
	{
		collider = std::make_unique<Collider>(this);
	}
}
