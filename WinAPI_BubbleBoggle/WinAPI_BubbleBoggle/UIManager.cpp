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
		// 1. Focused UI ã��
		// 2. ã�� UI���� �̺�Ʈ ã��
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

		// ����� ������ ��
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

		// 1. �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�

		// Ʈ�� ������ ��ȸ �ϸ鼭 !!

		// 2. UI�� Target �Ǿ��ٴ� �� ���� ���� UI�� Check �ؾ� �Ѵ�!
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
			// ť���� ������ �ϳ� ������
			UI* currUI{ q.front() };
			q.pop();

			// Target UI �����ͷ� �ش� UI �ּ� ���� ���� �� ����!
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
		// �̹� ��Ŀ���� �ܿ�
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