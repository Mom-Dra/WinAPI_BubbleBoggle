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
			// �ٷ� ���� ���ϰ�, Dead ���·� �ٲ۴���
			// ������ Update �ֵ鵵 �پ� �� �ֵ���
			// �� ���� �����ӿ� ���� ������ ����!

			// lParam : Object Address\
			// Object�� Dead���·� ����
			// ���� ���� ������Ʈ�� ��͵д�

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
