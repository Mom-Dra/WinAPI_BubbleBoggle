#include "SceneTool.h"
#include "KeyManager.h"
#include "Tile.h"
#include "Core.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "resource.h"
#include "SceneManager.h"
#include "UI.h"
#include "PanelUI.h"
#include "BtnUI.h"
#include "UIManager.h"

namespace MomDra
{
	void ChangeScene(DWORD_PTR, DWORD_PTR);

	SceneTool::SceneTool(const std::wstring& name) noexcept : Scene{ name }, ui{ nullptr }
	{

	}

	void SceneTool::Update() const noexcept
	{
		Scene::Update();

		SetTileIndex();
	}

	void SceneTool::Enter() noexcept
	{
		// 타일 생성
		CreateTile(5, 5);

		// UI 하나 만들기
		const Vector2& resolution{ Core::GetInstance().GetResolution() };

		std::unique_ptr<PanelUI> panelUI{ std::make_unique<PanelUI>(false, Layer::UI) };
		panelUI->SetScale(Vector2{ 200.0f, 100.0f });
		panelUI->SetPos(Vector2{ resolution.X - panelUI->GetScale().X, 0.0f });
		panelUI->SetName(L"Parent");

		std::shared_ptr<BtnUI> childBtnUI{ std::make_shared<BtnUI>(Vector2{50.0f, 0.0f}, Vector2{100.0f, 40.0f}, false, Layer::UI) };
		childBtnUI->SetName(L"Child");
		childBtnUI->SetClickedCallFunc(ChangeScene, 0, 0);

		panelUI->AddChild(childBtnUI);

		std::unique_ptr<PanelUI> panelUICloned{ std::make_unique<PanelUI>(*panelUI) };
		panelUICloned->SetPos(panelUICloned->GetPos() + Vector2{ 0.0f, 50.0f });

		ui = panelUICloned.get();

		AddObject(std::move(panelUI));
		AddObject(std::move(panelUICloned));

		// Camera Look At 지정
		Camera::GetInstance().SetLookAt(resolution / 2.0f);
	}

	void SceneTool::Exit() noexcept
	{
		DeleteAllObject();
	}

	void SceneTool::SetTileIndex() const noexcept
	{
		if (KeyManager::GetInstance().GetKeyDown(Key::LBUTTON))
		{
			Vector2 mousePos{ KeyManager::GetInstance().GetMousePos() };
			mousePos = Camera::GetInstance().GetRealPos(mousePos);

			const auto& [tileX, tileY] { GetTileXY() };

			int col{ static_cast<int>(mousePos.X / Tile::TILE_SIZE) };
			int row{ static_cast<int>(mousePos.Y / Tile::TILE_SIZE) };

			if (mousePos.X < 0.0f || tileX <= static_cast<unsigned int>(col) || mousePos.Y < 0.0f || tileY <= static_cast<unsigned int>(row))
				return;

			unsigned int idx{ row * tileX + col };

			const std::vector<std::unique_ptr<Object>>& tileVec{ GetLayerObject(Layer::TILE) };
			
			Tile* tile{ dynamic_cast<Tile*>(tileVec[idx].get()) };
			tile->AddImgIndex();
		}
	}

	void ChangeScene(DWORD_PTR, DWORD_PTR)
	{
		EventManager::GetInstance().ChangeScene(SceneType::START);
	}

	// Tile Count Windows Proc
	INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK)
			{
				unsigned int xCount{ GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false) };
				unsigned int yCount{ GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false) };

				Scene* currScene{ SceneManager::GetInstance().GetCurrentScene() };
				SceneTool* toolScene{ dynamic_cast<SceneTool*>(currScene) };

				if (!toolScene)
					throw std::runtime_error("It's Not Tool Scene");

				toolScene->DeleteLayerObject(Layer::TILE);
				toolScene->CreateTile(xCount, yCount);

				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			else if (LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
		return (INT_PTR)FALSE;
	}
}
