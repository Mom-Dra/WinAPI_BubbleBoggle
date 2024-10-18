#pragma once

#include "Tag.h"
#include "Vector2.h"
#include <vector>

using namespace CK;

namespace MomDra
{
	struct Rectangle2D
	{
		Vector2 min;
		Vector2 max;
	};

	class Ray
	{
	private:
		using RayPos = std::pair<Vector2, Vector2>;
		static inline std::vector<RayPos> rays;

	public:
		static bool RayCast(const Vector2& start, const Vector2& dir, const Layer& layer, Collider*& outCollider);
		static void DebugRay(const Vector2& start, const Vector2& dir);

		static void Render(const HDC& hdc) noexcept;
		
	private:
		explicit Ray() noexcept = delete;
		explicit Ray(const Ray& other) = delete;
		explicit Ray(const Ray&& other) = delete;

		Ray& operator=(const Ray& other) = delete;
		Ray& operator=(const Ray&& other) = delete;

		static bool IntersectRectangle(const Vector2& start, const Vector2& dir, const Rectangle2D& rect);
	};
}
