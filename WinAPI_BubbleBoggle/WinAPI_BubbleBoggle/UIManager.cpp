#include "UIManager.h"
#include "SceneManager.h"
#include "UI.h"
#include "KeyManager.h"
#include <queue>

namespace MomDra
{
	UIManager& UIManager::GetInstance() noexcept
	{
		static UIManager instance;

		return instance;
	}

	void UIManager::Update() noexcept
	{
		// 1. Focused UI 찾기
		// 2. 찾은 UI에서 이벤트 찾기
		bool lBtnTap{ KeyManager::GetInstance().GetKeyDown(Key::LBUTTON) };
		bool lBtnAway{ KeyManager::GetInstance().GetKeyUp(Key::LBUTTON) };

		focusedUI = GetFocusedUI();

		if (!focusedUI) return;

		UI* ui = GetTargetUI(focusedUI);

		if (ui)
		{
			ui->MouseOn();

			if (lBtnTap)
			{
				ui->MouseLBtnDown();
				ui->SetIsLBtnDown(true);
			}
			else if (lBtnAway)
			{
				ui->MouseLBtnUp();

				if (ui->IsLBtnDown())
				{
					ui->MouseLBtnClicked();
				}

				ui->SetIsLBtnDown(false);
			}
		}
	}

	UI* UIManager::GetFocusedUI() noexcept
	{
		Scene* currScene{ SceneManager::GetInstance().GetCurrentScene() };
		std::vector<std::unique_ptr<Object>>& uiVec{ currScene->GetUILayerObject() };

		UI* focusedUI{ this->focusedUI };

		bool lBtnTap{ KeyManager::GetInstance().GetKeyDown(Key::LBUTTON) };
		if (!lBtnTap) return focusedUI;

		auto targetIt{ uiVec.rbegin() };
		auto it{ uiVec.rbegin() };
		for (; it != uiVec.rend(); ++it)
		{
			UI* ui{ dynamic_cast<UI*> (it->get()) };

			if (ui->IsMouseOn())
			{
				targetIt = it;
				break;
			}
		}

		// 허공을 눌렀을 때
		if (it == uiVec.rend())
		{
			return nullptr;
		}

		auto normalIt{ std::prev(targetIt.base()) };
		focusedUI = dynamic_cast<UI*>(normalIt->get());

		std::unique_ptr<Object> deleted{ std::move(*normalIt) };

		uiVec.erase(normalIt);
		uiVec.emplace_back(std::move(deleted));

		return focusedUI;
	}

	UI* UIManager::GetTargetUI(UI* parentUI) const noexcept
	{
		bool lBtnAway{ KeyManager::GetInstance().GetKeyUp(Key::LBUTTON) };

		UI* targetUI{ nullptr };

		// 1. 부모 UI 포함, 모든 자식들을 검사한다

		// 트리 구조를 순회 하면서 !!

		// 2. UI가 Target 되었다는 걸 여러 개의 UI가 Check 해야 한다!
		static std::queue<UI*> q;
		static std::vector<UI*> nonTargetVec;

		while (!q.empty())
		{
			q.pop();
		}

		nonTargetVec.clear();

		q.emplace(parentUI);

		while (!q.empty())
		{
			// 큐에서 데이터 하나 꺼내기
			UI* currUI{ q.front() };
			q.pop();

			// Target UI 포인터로 해당 UI 주소 값을 가져 올 것임!
			if (currUI->IsMouseOn())
			{
				if (targetUI)
				{
					nonTargetVec.emplace_back(targetUI);
				}

				targetUI = currUI;
			}
			else
			{
				nonTargetVec.emplace_back(currUI);
			}

			const std::vector<std::shared_ptr<UI>>& childUIs{ currUI->GetChildren() };
			for (const auto& childUI : childUIs)
			{
				q.emplace(childUI.get());
			}
		}

		if (lBtnAway)
		{
			for (const auto& nonTargetUI : nonTargetVec)
			{
				nonTargetUI->SetIsLBtnDown(false);
			}
		}

		return targetUI;
	}

	void UIManager::SetFocusedUI(UI* ui) noexcept
	{
		// 이미 포커싱인 겨우
		if (focusedUI == ui || ui == nullptr)
		{
			focusedUI = ui;

			return;
		}

		focusedUI = ui;

		Scene* curScene{ SceneManager::GetInstance().GetCurrentScene() };
		std::vector<std::unique_ptr<Object>>& uiVec{ curScene->GetUILayerObject() };

		auto it{ uiVec.begin() };

		for (; it != uiVec.end(); ++it)
		{
			UI* tmp{ dynamic_cast<UI*>(it->get()) };
			if (tmp == focusedUI)
			{
				break;
			}
		}

		std::unique_ptr<Object> deleted{ std::move(*it) };

		uiVec.erase(it);
		uiVec.emplace_back(std::move(deleted));
	}
}