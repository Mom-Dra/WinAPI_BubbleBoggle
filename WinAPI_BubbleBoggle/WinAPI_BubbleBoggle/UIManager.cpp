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

	void UIManager::Update() const noexcept
	{
		Scene* currScene{ SceneManager::GetInstance().GetCurrentScene() };
		const std::vector<std::unique_ptr<Object>>& UIObjects{ currScene->GetLayerObject(Layer::UI) };

		bool lBtnTap{ KeyManager::GetInstance().GetKeyDown(Key::LBUTTON) };
		bool lBtnAway{ KeyManager::GetInstance().GetKeyUp(Key::LBUTTON) };

		for (const auto& uiObject : UIObjects)
		{
			UI* ui{ dynamic_cast<UI*> (uiObject.get()) };

			ui = GetTargetUI(ui);
			
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
	}

	UI* UIManager::GetTargetUI(UI* parentUI) const noexcept
	{
		bool lBtnAway{ KeyManager::GetInstance().GetKeyUp(Key::LBUTTON) };

		UI* targetUI{ nullptr };
		// 1. 부모 UI 포함, 모든 자식들을 검사한다

		// 트리 구조를 순회 하면서 !!
		// 재귀 함수?

		// 2. UI가 Target 되었다는 걸 여러 개의 UI가 Check 해야 한다!
		// BFS라고 합니다!!
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
}