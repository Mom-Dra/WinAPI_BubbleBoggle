#pragma once
#include "framework.h"
#include "Vector2.h"
#include "Collider.h"
#include <string>
#include <memory>
#include "Tag.h"
#include "EventManager.h"

using namespace CK;

namespace MomDra
{
	class Object
	{
	private:
		Vector2 pos;
		Vector2 scale;

		std::unique_ptr<Collider> collider;

		Layer layer;
		std::wstring name;

		bool isAlive;

	public:
		explicit Object(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::DEFAULT) noexcept;
		explicit Object(const Object& other) noexcept;
		virtual ~Object() noexcept = default;

		inline void SetPos(Vector2 pos) noexcept { this->pos = pos; }
		inline void SetScale(Vector2 scale) noexcept { this->scale = scale; }
		inline void SetName(const std::wstring& name) noexcept { this->name = name; }

		inline const Vector2& GetPos() const noexcept { return pos; }
		inline const Vector2& GetScale() const noexcept { return scale; }
		inline const std::wstring& GetName() const noexcept { return name; }
		inline const Layer& GetLayer() const noexcept { return layer; }
		inline bool IsDead() const noexcept { return !isAlive; }

		virtual void Update() noexcept = 0;
		virtual void LateUpdate() noexcept final;
		virtual void Render(const HDC& hdc) const noexcept;

		Collider* GetCollider() const noexcept;

		virtual void OnCollisionEnter(const Collider* other) {};
		virtual void OnCollisionStay(const Collider* other) {};
		virtual void OnCollisionExit(const Collider* other) {};

	protected:
		void CreateCollider(const Vector2& scale) noexcept;
		void ComponentRender(const HDC& hdc) const noexcept;

	private:
		inline void SetDead() noexcept { isAlive = false; }

		friend class EventManager;
	};
}
