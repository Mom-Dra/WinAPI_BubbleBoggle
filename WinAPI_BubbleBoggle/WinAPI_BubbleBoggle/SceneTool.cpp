#include "SceneTool.h"
#include "KeyManager.h"
#include "Tile.h"
#include "Core.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "resource.h"
#include "SceneManager.h"
#include "UI.h"

namespace MomDra
{
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

		UI* ui = new UI{ Layer::UI };
		ui->SetScale(Vector2{ 100.0f, 30.0f });
		ui->SetPos(Vector2{ resolution.X - ui->GetScale().X, 0.0f });

		AddObject(ui);

		// Camera Look At 지정
		Camera::GetInstance().SetLookAt(resolution / 2.0f);
	}

	void SceneTool::Exit() noexcept
	{
		
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

			if (mousePos.X < 0.0f || tileX <= col || mousePos.Y < 0.0f || tileY <= row)
				return;

			unsigned int idx{ row * tileX + col };

			const std::vector<std::unique_ptr<Object>>& tileVec{ GetLayerObject(Layer::TILE) };
			
			Tile* tile{ dynamic_cast<Tile*>(tileVec[idx].get()) };
			tile->AddImgIndex();
		}
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
