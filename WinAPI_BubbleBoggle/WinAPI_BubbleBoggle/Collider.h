#pragma once
#include "framework.h"
#include "Vector2.h"

using namespace CK;

namespace MomDra
{
	class Object;

	class Collider
	{
	private:
		Object* owner;

		Vector2 offSetPos;
		Vector2 finalPos;

		Vector2 scale;

	public:
		explicit Collider(Object* owner) noexcept;

		inline void SetOffSetPos(const Vector2& pos) { offSetPos = pos; }
		inline void SetScale(const Vector2& scale) { this->scale = scale; }

		inline const Vector2& GetOffSetPos() { return offSetPos; }
		inline const Vector2& GetScale() { return scale; }

		void LateUpdate() noexcept;
		void Render(const HDC& hdc) noexcept;
	};
}
