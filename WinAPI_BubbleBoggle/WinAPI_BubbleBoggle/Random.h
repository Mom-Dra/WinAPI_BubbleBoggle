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
		explicit Random(const Random& other) noexcept = delete;
		explicit Random(Random&& other) noexcept = delete;

		Random& operator=(const Random& other) noexcept = delete;
		Random& operator=(Random&& other) noexcept = delete;
	};
}
