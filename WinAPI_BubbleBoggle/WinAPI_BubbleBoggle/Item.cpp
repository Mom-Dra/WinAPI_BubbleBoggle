#include "Item.h"
#include "SelectGDI.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Player.h"

namespace MomDra
{
	Item::Item(const Vector2& pos, const std::wstring& imgPath, const Vector2& scale, const Layer& layer) noexcept : ImageObject{ pos, scale, imgPath, layer }
	{
		CreateCollider(scale);
		CreateRigidbody();
		CreateAnimator();

		GetAnimator()->LoadAnimation(L"\\animation\\Player_Destroy.anim");
	}

	void Item::Update() noexcept
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		time += timeManager.GetDeltaTime();

		if (!isDestroy && time >= DESTROY_ANIM_TIME)
		{
			isDestroy = true;
			GetAnimator()->StopAndPlayOneShot(PlayerSetting::DESTROY);
		}
		else if (time >= DESTROY_ANIM_TIME + DESTROY_TIME)
			Destroy();

		if (time >= CAN_COLLISION_TIME)
			canCollision = true; 
	}

	void Item::Render(const HDC& hdc) const noexcept
	{
		if (isDestroy) Object::Render(hdc);
		else ImageObject::Render(hdc);
	}

	void Item::OnCollisionEnter(const Collider* other)
	{
		if (!canCollision || isDestroy) return;

		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Player:
			DestroyItem();
			break;
		}
	}

	void Item::OnCollisionStay(const Collider* other)
	{
		if (!canCollision || isDestroy) return;

		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Player:
			DestroyItem();
			break;
		}
	}

	void Item::DestroyItem()
	{
		if (isDestroy) return;

		ResourceManager::GetInstance().LoadSound(L"\\sound\\Item.wav")->Play();
		Destroy();
	}
}