#pragma once
#include <random>

namespace MomDra
{
	class Random
	{
	public:
		static inline std::random_device rd;
		static inline std::default_random_engine gen{ rd() };
		
		// 0 ~ 100 È®·ü ÀÔ·Â
		static bool GetPossibility(int possibility);

	private:
		explicit Random() noexcept = delete;
		explicit Random(const Random& other) = delete;
		explicit Random(const Random&& other) = delete;

		Random& operator=(const Random& other) = delete;
		Random& operator=(const Random&& other) = delete;
	};
}
