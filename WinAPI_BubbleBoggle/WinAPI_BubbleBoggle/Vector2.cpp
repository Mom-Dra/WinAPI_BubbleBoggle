#include "Vector2.h"
#include <cmath>
using namespace CK;

const Vector2 Vector2::UnitX(1.f, 0.f);
const Vector2 Vector2::UnitY(0.f, 1.f);
const Vector2 Vector2::Zero(0.f, 0.f);
const Vector2 Vector2::One(1.f, 1.f);

std::string Vector2::ToString() const
{
	char result[64];
	std::snprintf(result, sizeof(result), "(%.3f, %.3f)", X, Y);
	return result;
}

Vector2 Vector2::GetNormalize() const
{
	float squareSum = SizeSquared();

	if (squareSum == 1.0f)
	{
		return *this;
	}
	else if (squareSum == 0.0f)
	{
		return Vector2::Zero;
	}

	return Vector2(X, Y) / std::sqrt(squareSum);
}