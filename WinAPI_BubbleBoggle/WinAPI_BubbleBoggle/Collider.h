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
		static inline unsigned int sID{ 0 };

		Object* owner;

		Vector2 offSetPos;
		Vector2 finalPos;

		Vector2 scale;

		unsigned int id;
		int colCount;

	public:
		explicit Collider(Object* owner) noexcept;
		explicit Collider(Object* owner, const Vector2& scale) noexcept;
		explicit Collider(const Collider& other) noexcept;
		Collider& operator=(const Collider& other) noexcept = delete;

		inline void SetOffSetPos(const Vector2& pos) { offSetPos = pos; }
		inline void SetScale(const Vector2& scale) { this->scale = scale; }

		inline const Vector2& GetOffSetPos() const noexcept { return offSetPos; }
		inline const Vector2& GetScale() const noexcept { return scale; }
		inline const Vector2& GetFinalPos() const noexcept { return finalPos; }

		inline unsigned int GetId() const noexcept { return id; }

		inline Object* GetObj() const noexcept { return owner; }

		void LateUpdate() noexcept;
		void Render(const HDC& hdc) noexcept;

	public:
		void OnCollisionStay(const Collider* other) noexcept;
		void OnCollisionEnter(const Collider* other) noexcept;
		void OnCollisionExit(const Collider* other) noexcept;
	};
}
