#include "Camera.h"
#include "Core.h"
#include "KeyManager.h"

namespace MomDra
{
    Camera::Camera() noexcept : targetObject{ nullptr }, followingTime{ 0.5f }, followingSpeed{ 0.0f }, accTime{ 0.0f }
    {
       
    }

    Camera& Camera::GetInstance() noexcept
    {
        static Camera instance;

        return instance;
    }

    void Camera::Update()
    {
        if (targetObject)
        {
            if (targetObject->IsDead())
                targetObject = nullptr;
            else
            {
                lookAt = targetObject->GetPos();
            }
        }

        float deltatime{ TimeManager::GetInstance().GetDeltaTime() };

        if (KeyManager::GetInstance().GetKey(Key::UP))
        {
            lookAt.Y -= 500.0f * deltatime;
        }

        if (KeyManager::GetInstance().GetKey(Key::DOWN))
        {
            lookAt.Y += 500.0f * deltatime;
        }

        if (KeyManager::GetInstance().GetKey(Key::LEFT))
        {
            lookAt.X -= 500.0f * deltatime;
        }

        if (KeyManager::GetInstance().GetKey(Key::RIGHT))
        {
            lookAt.X += 500.0f * deltatime;
        }

        // 화면 중앙좌표와 카메라 LookAt 좌표간의 사이값 계산
        CalDiff();
    }

    void Camera::CalDiff() noexcept
    {
        // 이전 LookAt과 현재 Look의 차이값을 보정해서 핸져의 LookAt을 구한다
        // lookAt

        // 이런 경우에는 시간 개념 (ex 10초)
        // 10초 이상 넘어가면 그 위치로 세팅 해주는 방법으로!
        float deltaTime{ TimeManager::GetInstance().GetDeltaTime() };
        accTime += deltaTime;

        if (followingTime <= accTime)
        {
            currLookAt = lookAt;
        }
        else
        {
            Vector2 lookDir{ lookAt - prevLookAt };
            currLookAt = prevLookAt + lookDir.GetNormalize() * followingSpeed * deltaTime;
        }

        const Vector2& resolution{ Core::GetInstance().GetResolution() };
        const Vector2 center{ resolution / 2.0f };

        diff = currLookAt - center;
        prevLookAt = currLookAt;
    }
}
