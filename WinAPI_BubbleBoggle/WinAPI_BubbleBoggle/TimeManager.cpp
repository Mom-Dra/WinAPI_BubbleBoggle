#include "TimeManager.h"
#include "framework.h"
#include <string>
#include "Core.h"

namespace MomDra
{
	TimeManager& TimeManager::GetInstance() noexcept
	{
		static TimeManager instance;

		return instance;
	}

	void TimeManager::Initialize() noexcept
	{
		// ���� ī��Ʈ
		QueryPerformanceCounter(&prevCount);

		// �ʴ� ī��Ʈ Ƚ��
		QueryPerformanceFrequency(&frequency);
	}

	float TimeManager::GetDeltaTime() const noexcept
	{
		return static_cast<float>(deltaTime);
	}

	void TimeManager::Update() noexcept
	{
		// ���� ī��Ʈ
		QueryPerformanceCounter(&currCount);

		// 1 frame�� �ɸ� �ð� ���� ���ϰ� �ʹ�
		// frequency���� �̹� 1�ʴ� ī��Ʈ Ƚ���� ������ �ִ�
		deltaTime = static_cast<double>((currCount.QuadPart - prevCount.QuadPart)) / frequency.QuadPart;

		prevCount = currCount;

#ifdef _DEBUG
		if (deltaTime > (1.0f / 60.0f))
			deltaTime = 1.0f / 60.0f;
#endif // _DEBUG
	}

	void TimeManager::Render() noexcept
	{
		++updateCallCount;
		time += deltaTime;

		if (time >= 1.0)
		{
			fps = updateCallCount;
			updateCallCount = 0;
			time = 0.0;

			std::wstring buffer;
			buffer.append(L"FPS: " + std::to_wstring(fps) + L" Deltatime: " + std::to_wstring(deltaTime));
			SetWindowText(Core::GetInstance().GetMainHwnd(), buffer.data());
		}
	}
}
