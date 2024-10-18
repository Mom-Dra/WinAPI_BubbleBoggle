#include "Ray.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SelectGDI.h"
#include "Core.h"
#include <array>

namespace MomDra
{
	bool Ray::RayCast(const Vector2& start, const Vector2& dir, const Layer& layer, Collider*& outCollider)
	{
		const std::vector<std::unique_ptr<Object>>& objects{ SceneManager::GetInstance().GetCurrentScene()->GetLayerObject(layer) };

		for (const auto& object : objects)
		{
			Collider* collider{ object->GetCollider() };

			const Vector2& pos{ collider->GetFinalPos() };
			const Vector2& scale{ collider->GetScale() };

			Rectangle2D rect{ pos - scale / 2.0f, pos + scale / 2.0f };

			if (IntersectRectangle(start, dir, rect))
			{
				outCollider = collider;
				return true;
			}
		}

		return false;
	}

	void Ray::DebugRay(const Vector2& start, const Vector2& dir)
	{
		Vector2 end{ start + dir };

		rays.emplace_back(start, end);
	}

	void Ray::Render(const HDC& hdc) noexcept
	{
		SelectGDI gdi{ hdc, PenType::Red };
		for (const auto& [start, end] : rays)
		{
			MoveToEx(hdc, static_cast<int>(start.X), static_cast<int>(start.Y), nullptr);
			LineTo(hdc, static_cast<int>(end.X), static_cast<int>(end.Y));
		}

		rays.clear();
	}

	bool Ray::IntersectRectangle(const Vector2& start, const Vector2& dir, const Rectangle2D& rect)
	{
		float t_min{ 0.0f };
		float t_max{ dir.Size() };

		Vector2 dirNomal{ dir.GetNormalize() };

		for (int i{ 0 }; i < 2; i++) {
			float rayOrigin{ (i == 0 ? start.X : start.Y) };
			float rayDirection{ (i == 0 ? dirNomal.X : dirNomal.Y) };
			float rectMin{ (i == 0 ? rect.min.X : rect.min.Y) };
			float rectMax{ (i == 0 ? rect.max.X : rect.max.Y) };

			float invD{ 1.0f / rayDirection };
			float t0{ (rectMin - rayOrigin) * invD };
			float t1{ (rectMax - rayOrigin) * invD };

			if (invD < 0.0f) std::swap(t0, t1);

			t_min = t0 > t_min ? t0 : t_min;
			t_max = t1 < t_max ? t1 : t_max;

			// t_max가 t_min보다 작거나 최대 거리를 넘으면 교차하지 않음
			if (t_max <= t_min || t_max < 0.0f)
			{
				return false;  // 교차하지 않음
			}
		}

		// t_min이 최대 거리 이내인지 확인
		return t_min <= t_max;

	}
}