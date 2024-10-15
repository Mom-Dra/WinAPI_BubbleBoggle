#pragma once
#include "framework.h"
#include "Vector2.h"
#include "Collider.h"
#include <string>
#include <memory>
#include "Tag.h"
#include "EventManager.h"
#include "Animator.h"
#include "RigidBody.h"

using namespace CK;

namespace MomDra
{
	class Object
	{
	private:
		Vector2 pos;
		Vector2 scale;

		// Component
		std::unique_ptr<Collider> collider;
		std::unique_ptr<Animator> animator;
		std::unique_ptr<RigidBody> rigidbody;

		Layer layer;
		std::wstring name;

		bool isAlive;

	public:
		explicit Object(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::DEFAULT) noexcept;
		explicit Object(const Object& other) noexcept;
		virtual ~Object() noexcept = default;

		inline void SetPos(const Vector2& pos) noexcept { this->pos = pos; }
		inline void SetScale(const Vector2& scale) noexcept { this->scale = scale; }
		inline void SetName(const std::wstring& name) noexcept { this->name = name; }

		inline const Vector2& GetPos() const noexcept { return pos; }
		inline const Vector2& GetScale() const noexcept { return scale; }
		inline const std::wstring& GetName() const noexcept { return name; }
		inline const Layer& GetLayer() const noexcept { return layer; }
		inline Collider* GetCollider() const noexcept { return collider.get(); }
		inline Animator* GetAnimator() const noexcept { return animator.get(); }
		inline RigidBody* GetRigidBody() const noexcept { return rigidbody.get(); }
		inline bool IsDead() const noexcept { return !isAlive; }

		virtual void Start() {};
		virtual void Update() noexcept = 0;
		virtual void LateUpdate() noexcept;
		virtual void Render(const HDC& hdc) const noexcept;

		virtual void OnCollisionEnter(const Collider* other) {};
		virtual void OnCollisionStay(const Collider* other) {};
		virtual void OnCollisionExit(const Collider* other) {};

		virtual std::unique_ptr<Object> Clone() const = 0;

	protected:
		inline void CreateCollider(const Vector2& scale) noexcept { collider = std::make_unique<Collider>(this, scale); }
		inline void CreateCollider() noexcept { collider = std::make_unique<Collider>(this); }
		inline void CreateAnimator() noexcept { animator = std::make_unique<Animator>(this); }
		inline void CreateRigidbody() noexcept { rigidbody = std::make_unique<RigidBody>(this); }
		void ComponentRender(const HDC& hdc) const noexcept;

	private:
		inline void SetDead() noexcept { isAlive = false; }

		friend class EventManager;
	};
}
