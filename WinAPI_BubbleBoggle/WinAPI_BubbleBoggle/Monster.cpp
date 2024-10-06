#include "Monster.h"

namespace MomDra
{
	Monster::Monster(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath) : ImageObject{ pos, scale, imgPath }
	{
		CreateCollider();
		Collider* collider{ GetCollider() };
		collider->SetScale(Vector2{ 100.0f, 100.0f });
	}
}