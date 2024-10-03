#pragma once

#include "framework.h"

namespace MomDra
{
	class TimeManager
	{
	private:
		LARGE_INTEGER frequency{ 0 };
		LARGE_INTEGER currCount{ 0 };
		LARGE_INTEGER prevCount{ 0 };

		double deltaTime{ 0.0 };
		double time{ 0.0 };

		unsigned int fps{ 0 };
		unsigned int updateCallCount{ 0 };

	public:
		static TimeManager& GetInstance() noexcept;
		void Initialize() noexcept;

		float GetDeltaTime() const noexcept;
		void Update() noexcept;

	private:
		explicit TimeManager() = default;
		explicit TimeManager(const TimeManager& other) = delete;
		TimeManager& operator=(const TimeManager& other) = delete;
	};
}
