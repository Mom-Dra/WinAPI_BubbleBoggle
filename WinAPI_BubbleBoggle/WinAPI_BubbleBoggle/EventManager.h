#pragma once
#include "framework.h"
#include "Tag.h"
#include <vector>
#include "Object.h"

namespace MomDra
{
	struct Event
	{
		EventType eventType;
		DWORD_PTR lParam;
		DWORD_PTR wParam;
	};

	class EventManager
	{
	private:
		std::vector<Event> events;

	public:
		static EventManager& GetInstance() noexcept;

		void Update();
		void Instantiate(Object* obj) noexcept;
		void Destory(Object* obj) noexcept;
		void ChangeScene(const SceneType& sceneType) noexcept;

	private:
		explicit EventManager() noexcept = default;
		explicit EventManager(const EventManager& other) = delete;
		EventManager& operator=(const EventManager& other) = delete;

		inline void AddEvent(const Event& event) noexcept { events.emplace_back(event); }
		void Execute(const Event& event);
	};
}
