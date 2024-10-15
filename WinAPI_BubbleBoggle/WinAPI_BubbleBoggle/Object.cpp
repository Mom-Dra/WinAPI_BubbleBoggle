#include "Object.h"
#include "Camera.h"

namespace MomDra
{
	Object::Object(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept : pos{ pos }, scale{ scale }, isAlive{ true }, layer{ layer }
	{

	}

	Object::Object(const Object& other) noexcept : pos{ other.pos }, scale{ other.scale }, isAlive{ true }, name{ other.name }, layer{ other.layer }
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

		if (other.rigidbody)
		{
			rigidbody = std::make_unique<RigidBody>(*other.rigidbody);
			rigidbody->SetOwner(this);
		}
	}

	void Object::LateUpdate() noexcept
	{
		if (collider)
			collider->LateUpdate();

		// Update ��ġ ����??
		if (animator)
			animator->LateUpdate();

		if (rigidbody)
			rigidbody->LateUpdate();
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
