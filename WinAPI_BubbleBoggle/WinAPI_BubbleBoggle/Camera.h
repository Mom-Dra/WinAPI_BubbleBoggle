#pragma once
#include "Vector2.h"

using namespace CK;

namespace MomDra
{
	class Object;

	class Camera
	{
	private:
		Vector2 lookAt; // 카메라가 보는 위치
		Vector2 currLookAt; // 이전 위치, 현재 위치 보정 위치
		Vector2 prevLookAt; // 이전 프레임 바라봐야 하는 위치, 급격하게 변하면 천천히 바라보게 해야 함

		Object* targetObject; // 카메라 타켓 오브젝트
		Vector2 diff; // 해상도 중앙위치와, 카메라 LookAt 간의 차이 값

		float followingTime; // 타켓을 따라가는 시간
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
