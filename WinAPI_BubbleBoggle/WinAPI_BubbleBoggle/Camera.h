#pragma once
#include "Vector2.h"

using namespace CK;

namespace MomDra
{
	class Object;

	class Camera
	{
	private:
		Vector2 lookAt; // ī�޶� ���� ��ġ
		Vector2 currLookAt; // ���� ��ġ, ���� ��ġ ���� ��ġ
		Vector2 prevLookAt; // ���� ������ �ٶ���� �ϴ� ��ġ, �ް��ϰ� ���ϸ� õõ�� �ٶ󺸰� �ؾ� ��

		Object* targetObject; // ī�޶� Ÿ�� ������Ʈ
		Vector2 diff; // �ػ� �߾���ġ��, ī�޶� LookAt ���� ���� ��

		float followingTime; // Ÿ���� ���󰡴� �ð�
		float followingSpeed;
		float accTime;

	public:
		static Camera& GetInstance() noexcept;

		void Update();

		inline void SetLookAt(Vector2 look) noexcept
		{ 
			this->lookAt = look;
			float moveDistance{ (lookAt - prevLookAt).Size() };
			followingSpeed = moveDistance / followingTime;
			accTime = 0.0f;
		}
		inline void SetTarget(Object* targetObject) noexcept { this->targetObject = targetObject; }
		inline const Vector2& GetLookAt() const noexcept { return currLookAt; }
		inline Vector2 GetRenderPos(const Vector2& objPos) const noexcept { return objPos - diff; }
		inline Vector2 GetRealPos(const Vector2& renderPos) const noexcept { return renderPos + diff; }

	private:
		explicit Camera() noexcept;
		explicit Camera(const Camera& other) noexcept = delete;
		Camera& operator=(const Camera& other) noexcept = delete;

		void CalDiff() noexcept;
	};
}
