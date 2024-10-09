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

        // ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
        CalDiff();
    }

    void Camera::CalDiff() noexcept
    {
        // ���� LookAt�� ���� Look�� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�
        // lookAt

        // �̷� ��쿡�� �ð� ���� (ex 10��)
        // 10�� �̻� �Ѿ�� �� ��ġ�� ���� ���ִ� �������!
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
