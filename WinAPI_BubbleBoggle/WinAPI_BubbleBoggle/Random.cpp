#include "Random.h"

namespace MomDra
{
	bool Random::GetPossibility(int possibility)
	{
		if (possibility <= 0) return false;
		else if (possibility >= 100) return true;

		static std::uniform_int_distribution<int> dist{ 1, 100 };

		if (dist(gen) <= possibility)
		{
			return true;
		}

		return false;
	}
}