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
#include "CommandManager.h"

namespace MomDra
{
	void ChangeScene(DWORD_PTR, DWORD_PTR);

	SceneTool::SceneTool(const std::wstring& name) noexcept : Scene{ name }, ui{ nullptr }
	{

	}

	void SceneTool::Update() noexcept
	{
		static const KeyManager& keyManager{ KeyManager::GetInstance() };

		Scene::Update();

		SetTileIndex();

		if (KeyManager::GetInstance().GetKey(Key::CTRL))
		{
			MakeTileInput(true);
		}
		else
		{
			MakeTileInput(false);
		}

		if (KeyManager::GetInstance().GetKeyDown(Key::SPACE))
		{
			EventManager::GetInstance().ChangeScene(SceneType::START);
		}

		if (keyManager.GetKey(Key::CTRL))
		{
			if (keyManager.GetKeyDown(Key::S))
				SaveTileData();

			if (keyManager.GetKeyDown(Key::L))
				LoadTileData();

			if (keyManager.GetKeyDown(Key::Z))
				CommandManager::Undo();

			if (keyManager.GetKeyDown(Key::Y))
				CommandManager::Redo();
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

	void SceneTool::MakeTileInput(bool isWall) noexcept
	{
		static unsigned int startXPos;
		static unsigned int startYPos;
		static const Vector2& resolution{ Core::GetInstance().GetResolution() };

		if (KeyManager::GetInstance().GetKeyDown(Key::LBUTTON))
		{
			const Vector2& mousePos{ KeyManager::GetInstance().GetMousePos() };

			startXPos = { static_cast<unsigned int>(mousePos.X / TileRectangle::TILE_SIZE_X) };
			startYPos = { static_cast<unsigned int> (mousePos.Y / TileRectangle::TILE_SIZE_Y) };

			//CreateTileAtMousePos(startXPos, startYPos);
		}
		else if (KeyManager::GetInstance().GetKeyUp(Key::LBUTTON))
		{
			const Vector2& mousePos{ KeyManager::GetInstance().GetMousePos() };

			unsigned int endXPos = { static_cast<unsigned int>(mousePos.X / TileRectangle::TILE_SIZE_X) };
			unsigned int endYPos = { static_cast<unsigned int> (mousePos.Y / TileRectangle::TILE_SIZE_Y) };

			CreateTileAtMouseDrag(startXPos, startYPos, endXPos, endYPos, isWall);
		}
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

	void SceneTool::LoadTileData()
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
			std::wstring relativePath{ PathManager::GetRelativePath(name) };
			LoadTile(relativePath);

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

				toolScene->DeleteLayerObject(Layer::Tile);
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
