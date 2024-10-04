#pragma once
#include "framework.h"
#include "Vector2.h"
#include "Collider.h"
#include <string>
#include <memory>

using namespace CK;

namespace MomDra
{
	class Object
	{
	private:
		Vector2 pos;
		Vector2 scale;

		std::unique_ptr<Collider> collider;

	public:
		explicit Object() noexcept = default;
		explicit Object(const Vector2& pos, const Vector2& scale) noexcept;
		virtual ~Object() noexcept = default;

		void SetPos(Vector2 pos) noexcept;
		void SetScale(Vector2 scale) noexcept;

		const Vector2& GetPos() const noexcept;
		const Vector2& GetScale() const noexcept;

		virtual void Update() noexcept = 0;
		virtual void LateUpdate() noexcept final;
		virtual void Render(const HDC& hdc) const noexcept;

		Collider* GetCollider() const noexcept;

	protected:
		void CreateCollider() noexcept;
		void ComponentRender(const HDC& hdc) const noexcept;
	};
}
