#pragma once
#include <array>
#include <stdexcept>
#include <limits>
#include <numbers>
#include <algorithm>
#include <iostream>

#ifdef max
#undef max
#endif

namespace CK
{
	struct Vector2
	{
	public:
		// 생성자 
		inline constexpr Vector2() = default;
		inline explicit constexpr Vector2(int InX, int InY) : X(static_cast<float> (InX)), Y(static_cast<float> (InY)) { }
		inline explicit constexpr Vector2(float InX, float InY) : X(InX), Y(InY) { }

		// 연산자 
		inline constexpr float operator[](int InIndex) const;
		inline constexpr float& operator[](int InIndex);
		inline constexpr Vector2 operator-() const;
		inline constexpr Vector2 operator*(float InScalar) const;
		inline constexpr Vector2 operator/(float InScalar) const;
		inline constexpr Vector2 operator*(const Vector2& InVector) const;
		inline constexpr Vector2 operator+(const Vector2& InVector) const;
		inline constexpr Vector2 operator-(const Vector2& InVector) const;
		inline constexpr Vector2& operator*=(float InScale);
		inline constexpr Vector2& operator/=(float InScale);
		inline constexpr Vector2& operator+=(const Vector2& InVector);
		inline constexpr Vector2& operator-=(const Vector2& InVector);
		inline constexpr bool operator==(const Vector2& other) const noexcept;

		// 멤버함수 
		inline float Size() const;
		inline constexpr float SizeSquared() const;
		void Normalize();
		[[nodiscard]] Vector2 GetNormalize() const;
		inline bool EqualsInTolerance(const Vector2& InVector, float InTolerance = std::numeric_limits<float>::epsilon()) const;
		inline constexpr float Max() const;
		inline constexpr float Dot(const Vector2& InVector) const;
		inline float Angle() const;
		inline float AngleInDegree() const;
		inline Vector2 ToPolarCoordinate() const;
		inline constexpr Vector2 ToCartesianCoordinate() const;

		std::string ToString() const;

		// 정적멤버변수 
		static const Vector2 UnitX;
		static const Vector2 UnitY;
		static const Vector2 One;
		static const Vector2 Zero;
		static constexpr int Dimension{ 2 };

		// 멤버변수
		union
		{
			struct
			{
				float X, Y;
			};

			std::array<float, Dimension> Scalars{ 0.f, 0.f };
		};

	private:
		inline friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);
	};

	inline float Vector2::Size() const
	{
		return sqrtf(SizeSquared());
	}

	inline constexpr float Vector2::SizeSquared() const
	{
		return X * X + Y * Y;
	}

	inline void Vector2::Normalize()
	{
		*this = GetNormalize();
	}

	inline constexpr float Vector2::operator[](int InIndex) const
	{
		if (InIndex < 0 || InIndex >= Dimension)
			throw std::out_of_range("InIndex < 0 or InIndex >= Dimension");

		return Scalars[InIndex];
	}

	inline constexpr float& Vector2::operator[](int InIndex)
	{
		if (InIndex < 0 || InIndex >= Dimension)
			throw std::out_of_range("InIndex < 0 or InIndex >= Dimension");

		return Scalars[InIndex];
	}

	inline constexpr Vector2 Vector2::operator-() const
	{
		return Vector2(-X, -Y);
	}

	inline constexpr Vector2 Vector2::operator*(float InScalar) const
	{
		return Vector2(X * InScalar, Y * InScalar);
	}

	inline constexpr Vector2 Vector2::operator/(float InScalar) const
	{
		return Vector2(X / InScalar, Y / InScalar);
	}

	inline constexpr Vector2 Vector2::operator+(const Vector2& InVector) const
	{
		return Vector2(X + InVector.X, Y + InVector.Y);
	}

	inline constexpr Vector2 Vector2::operator-(const Vector2& InVector) const
	{
		return Vector2(X - InVector.X, Y - InVector.Y);
	}

	inline constexpr Vector2 Vector2::operator*(const Vector2& InVector) const
	{
		return Vector2(X * InVector.X, Y * InVector.Y);
	}

	inline constexpr Vector2& Vector2::operator*=(float InScale)
	{
		X *= InScale;
		Y *= InScale;
		return *this;
	}

	inline constexpr Vector2& Vector2::operator/=(float InScale)
	{
		X /= InScale;
		Y /= InScale;
		return *this;
	}

	inline constexpr Vector2& Vector2::operator+=(const Vector2& InVector)
	{
		X += InVector.X;
		Y += InVector.Y;
		return *this;
	}

	inline constexpr Vector2& Vector2::operator-=(const Vector2& InVector)
	{
		X -= InVector.X;
		Y -= InVector.Y;
		return *this;
	}

	inline constexpr bool Vector2::operator==(const Vector2& other) const noexcept
	{
		return X == other.X && Y == other.Y;
	}

	inline bool Vector2::EqualsInTolerance(const Vector2& InVector, float InTolerance) const
	{
		return (std::abs(this->X - InVector.X) <= InTolerance) &&
			(std::abs(this->Y - InVector.Y) < InTolerance);
	}

	inline constexpr float Vector2::Max() const
	{
		return std::max(X, Y);
	}

	inline constexpr float Vector2::Dot(const Vector2& InVector) const
	{
		return X * InVector.X + Y * InVector.Y;
	}

	inline float Vector2::Angle() const
	{
		return atan2f(Y, X);
	}

	inline float Vector2::AngleInDegree() const
	{
		return atan2f(Y, X) * 180.0f / std::numbers::pi_v<float>;
	}

	inline Vector2 Vector2::ToPolarCoordinate() const
	{
		return Vector2(Size(), Angle());
	}

	inline constexpr void GetSinCosRad(float& OutSin, float& OutCos, float InRadian)
	{
		// Copied from UE4 Source Code
		// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
		float quotient = ((1 / std::numbers::pi_v<float>) * 0.5f) * InRadian;
		if (InRadian >= 0.0f)
		{
			quotient = (float)((int)(quotient + 0.5f));
		}
		else
		{
			quotient = (float)((int)(quotient - 0.5f));
		}
		float y = InRadian - (2.0f * std::numbers::pi_v<float>) * quotient;

		// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
		float sign = 0.f;
		if (y > std::numbers::pi_v<float> / 2)
		{
			y = std::numbers::pi_v<float> -y;
			sign = -1.0f;
		}
		else if (y < -(std::numbers::pi_v<float> / 2))
		{
			y = -(std::numbers::pi_v<float>) - y;
			sign = -1.0f;
		}
		else
		{
			sign = +1.0f;
		}

		float y2 = y * y;

		// 11-degree minimax approximation
		OutSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

		// 10-degree minimax approximation
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
		OutCos = sign * p;
	}

	inline constexpr Vector2 Vector2::ToCartesianCoordinate() const
	{
		// 극좌표계에서 X는 반지름, Y는 각(rad)으로 활용
		float sin = 0.f, cos = 0.f;
		GetSinCosRad(sin, cos, Y);
		return Vector2(X * cos, X * sin);
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector2& vector)
	{
		os << '(' << vector.X << ", " << vector.Y << ')';
		return os;
	}
}