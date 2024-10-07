#include "EventManager.h"
#include "SceneManager.h"

namespace MomDra
{
	EventManager& EventManager::GetInstance() noexcept
	{
		static EventManager instance;

		return instance;
	}

	void EventManager::Update()
	{
		for (const Event& event : events)
		{
			Execute(event);
		}

		events.clear();
	}

	void EventManager::Instantiate(Object* obj) noexcept
	{
		Event event;
		event.eventType = EventType::CREATEOBJECT;
		event.lParam = (DWORD_PTR)(obj);

		AddEvent(event);
	}

	void EventManager::Destory(Object* obj) noexcept
	{
		Event event;
		event.eventType = EventType::DELETEOBJECT;
		event.lParam = (DWORD_PTR)(obj);

		AddEvent(event);
	}

	void EventManager::ChangeScene(const SceneType& sceneType) noexcept
	{
		Event event;
		event.eventType = EventType::CHANGESCENE;
		event.lParam = (DWORD_PTR)(sceneType);

		AddEvent(event);
	}

	void EventManager::Execute(const Event& event)
	{
		switch (event.eventType)
		{
		case EventType::CREATEOBJECT:
		{
			// lParam : Object Address
			// rParam : Layer

			Object* obj{ (Object*)event.lParam };
			Layer layer{ static_cast<Layer>(event.wParam) };

			SceneManager::GetInstance().GetCurrentScene()->AddObject(obj);
		}
		break;
		case EventType::DELETEOBJECT:
		{
			// 바로 삭제 안하고, Dead 상태로 바꾼다음
			// 나머지 Update 애들도 다알 수 있도록
			// 그 다음 프레임에 실제 삭제를 진행!

			// lParam : Object Address\
			// Object를 Dead상태로 변경
			// 삭제 예정 오브젝트를 모와둔다

			Object* obj{ (Object*)event.lParam };
			obj->SetDead();
		}
		break;
		case EventType::CHANGESCENE:
			// lParam : Next Scene Type
			SceneManager::GetInstance().ChangeScene(static_cast<SceneType>(event.lParam));
			break;
		}
	}
}
