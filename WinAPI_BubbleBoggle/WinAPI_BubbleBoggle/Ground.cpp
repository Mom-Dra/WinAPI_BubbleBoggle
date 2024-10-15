#include "Ground.h"

namespace MomDra
{
	Ground::Ground(const Vector2& pos, const Vector2& scale, const Layer& layer) : Object{ pos, scale, layer }
	{
		CreateCollider(scale);
	}

	void Ground::Start()
	{

	}

	void Ground::Update() noexcept
	{

	}

	void Ground::OnCollisionEnter(const Collider* other)
	{
		const Layer& otherLayer{ other->GetObj()->GetLayer() };

		if (otherLayer == Layer::PLAYER)
		{
			// rigidbody 쪽에 땅이라고 설정!

		}
		else if (otherLayer == Layer::MONSTER)
		{

		}
	}
}