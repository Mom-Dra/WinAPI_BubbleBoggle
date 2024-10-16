#include "SceneTool.h"
#include "KeyManager.h"
#include "Tile.h"
#include "TileRectangle.h"
#include "Core.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "resource.h"
#include "SceneManager.h"
#include "UI.h"
#include "PanelUI.h"
#include "BtnUI.h"
#include "UIManager.h"
#include <fstream>
#include <iostream>
#include "PathManager.h"
#include <commdlg.h>

namespace MomDra
{
	void ChangeScene(DWORD_PTR, DWORD_PTR);

	SceneTool::SceneTool(const std::wstring& name) noexcept : Scene{ name }, ui{ nullptr }
	{

	}

	void SceneTool::Update() noexcept
	{
		Scene::Update();

		SetTileIndex();

		if (KeyManager::GetInstance().GetKeyDown(Key::LSHIFT))
		{
			//SaveTile(L"\\tile\\Test.tile");
			SaveTileData();
		}

		if (KeyManager::GetInstance().GetKey(Key::LBUTTON))
		{
			const Vector2& mousePos{ KeyManager::GetInstance().GetMousePos() };
			const Vector2& resolution{ Core::GetInstance().GetResolution() };

			unsigned int xPos{ static_cast<unsigned int>(mousePos.X / TileRectangle::TILE_SIZE_X) };
			unsigned int yPos{ static_cast<unsigned int> (mousePos.Y / TileRectangle::TILE_SIZE_Y) };

			CreateTileAtMousePos(xPos, yPos);
		}

		/*if (KeyManager::GetInstance().GetKeyDown(Key::LSHIFT))
		{
			EventManager::GetInstance().ChangeScene(SceneType::START);
		}*/

		if (KeyManager::GetInstance().GetKeyDown(Key::CTRL))
		{
			LoadSceneData();
		}
	}

	void SceneTool::Enter() noexcept
	{
		// 타일 생성
		//CreateTile(5, 5);

		// UI 하나 만들기
		const Vector2& resolution{ Core::GetInstance().GetResolution() };

		/*std::unique_ptr<PanelUI> panelUI{ std::make_unique<PanelUI>(false, Layer::UI) };
		panelUI->SetScale(Vector2{ 200.0f, 100.0f });
		panelUI->SetPos(Vector2{ resolution.X - panelUI->GetScale().X, 0.0f });
		panelUI->SetName(L"Parent");

		std::shared_ptr<BtnUI> childBtnUI{ std::make_shared<BtnUI>(Vector2{50.0f, 0.0f}, Vector2{100.0f, 40.0f}, false, Layer::UI) };
		childBtnUI->SetName(L"Child");
		childBtnUI->SetClickedCallBack([this]() {this->SaveTileData(); });

		panelUI->AddChild(childBtnUI);

		std::unique_ptr<PanelUI> panelUICloned{ std::make_unique<PanelUI>(*panelUI) };
		panelUICloned->SetPos(panelUICloned->GetPos() + Vector2{ 0.0f, 50.0f });

		ui = panelUICloned.get();

		AddObject(std::move(panelUI));
		AddObject(std::move(panelUICloned));*/

		// Camera Look At 지정
		Camera::GetInstance().SetLookAt(resolution / 2.0f);
	}

	void SceneTool::Exit() noexcept
	{
		DeleteAllObject();
	}

	void SceneTool::SetTileIndex() const noexcept
	{
		/*if (KeyManager::GetInstance().GetKeyDown(Key::LBUTTON))
		{
			Vector2 mousePos{ KeyManager::GetInstance().GetMousePos() };
			mousePos = Camera::GetInstance().GetRealPos(mousePos);

			const auto& [tileX, tileY] { GetTileXY() };

			int col{ static_cast<int>(mousePos.X / Tile::TILE_SIZE_X) };
			int row{ static_cast<int>(mousePos.Y / Tile::TILE_SIZE_Y) };

			if (mousePos.X < 0.0f || tileX <= static_cast<unsigned int>(col) || mousePos.Y < 0.0f || tileY <= static_cast<unsigned int>(row))
				return;

			unsigned int idx{ row * tileX + col };

			const std::vector<std::unique_ptr<Object>>& tileVec{ GetLayerObject(Layer::TILE) };

			Tile* tile{ dynamic_cast<Tile*>(tileVec[idx].get()) };
			tile->AddImgIndex();
		}*/
	}

	void SceneTool::SaveTile(const std::wstring& path) const
	{
		/*std::wstring path{ PathManager::GetContentPath() };
		path.append(path);*/

		/*std::wofstream wOut{ path, std::ios::binary };

		if (!wOut.is_open())
		{
			std::wcout << "Can Not Open File Path: " << path << std::endl;
			return;
		}*/

		std::wofstream out{ path, std::ios::binary };
		//std::ofstream out{ path, std::ios::binary };

		if (!out.is_open())
		{
			std::wcout << "Can Not Open File Path: " << path << std::endl;
			return;
		}

		// 타일 개수 저장
		//const auto& [tileX, tileY] {GetTileXY()};

		//wOut << tileX << ' ' << tileY << ' ';

		//const std::vector<std::unique_ptr<Object>>& tiles{ GetLayerObject(Layer::TILE) };

		// 각 타일 각자의 데이터를 저장
		/*for (const auto& tile : tiles)
		{
			TileRectangle* tilePtr{ dynamic_cast<TileRectangle*>(tile.get()) };
			tilePtr->SaveFile(wOut);
		}*/

		TileRectangle::SaveFile(out);

		//std::cout << "Save File Complete - tileX: " << tileX << ", tileY: " << tileY << std::endl;
	}

	void SceneTool::SaveTileData()
	{
		OPENFILENAME ofn = {};

		std::wstring name;
		name.resize(256);

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = Core::GetInstance().GetMainHwnd();
		ofn.lpstrFile = &name[0];
		ofn.nMaxFile = static_cast<DWORD>(name.size());
		ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
		ofn.nFilterIndex = 0;
		ofn.lpstrFileTitle = nullptr;
		ofn.nMaxFileTitle = 0;

		std::wstring tilePath{ PathManager::GetContentPath() };
		tilePath.append(L"\\tile");

		ofn.lpstrInitialDir = tilePath.data();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		// Modal 방식
		// 그 해당 창이 포커싱이 되고, 나머지는 동작하지 않는다
		if (GetSaveFileName(&ofn))
		{
			SaveTile(name);

			std::wcout << "Save File Complete : " << name;
		} 
	}

	void SceneTool::LoadSceneData()
	{
		OPENFILENAME ofn = {};

		std::wstring name;
		name.resize(256);

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = Core::GetInstance().GetMainHwnd();
		ofn.lpstrFile = &name[0];
		ofn.nMaxFile = static_cast<DWORD>(name.size());
		ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
		ofn.nFilterIndex = 0;
		ofn.lpstrFileTitle = nullptr;
		ofn.nMaxFileTitle = 0;

		std::wstring tilePath{ PathManager::GetContentPath() };
		tilePath.append(L"\\tile");

		ofn.lpstrInitialDir = tilePath.data();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		// Modal 방식
		// 그 해당 창이 포커싱이 되고, 나머지는 동작하지 않는다
		if (GetOpenFileName(&ofn))
		{
			//std::wstring relativePath{ PathManager::GetRelativePath(name) };
			LoadTile(name);

			std::wcout << "Load File Complete: " << name << std::endl;
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
