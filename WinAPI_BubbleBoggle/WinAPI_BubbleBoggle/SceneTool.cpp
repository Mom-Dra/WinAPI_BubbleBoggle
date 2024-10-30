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
#include "AnimationObject.h"
#include "ImageObject.h"

namespace MomDra
{
	void ChangeScene(DWORD_PTR, DWORD_PTR);

	SceneTool::SceneTool(const std::wstring& name) noexcept : Scene{ name }, ui{ nullptr }
	{

	}

	void SceneTool::Enter() noexcept
	{
		AddObject(std::make_unique<ImageObject>(Core::GetInstance().GetResolution() / 2.0f, Core::GetInstance().GetResolution(), L"\\texture\\Stage1.bmp", Layer::DEFAULT));
		AddObject(std::make_unique<AnimationObject>());

		// Camera Look At 지정
		Camera::GetInstance().SetLookAt(Core::GetInstance().GetResolution() / 2.0f);
	}

	void SceneTool::Update() noexcept
	{
		static const KeyManager& keyManager{ KeyManager::GetInstance() };

		Scene::Update();

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
			EventManager::GetInstance().ChangeScene(SceneType::INTRO);
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

	void SceneTool::Exit() noexcept
	{
		DeleteAllObject();
	}

	void SceneTool::MakeTileInput(bool isWall) noexcept
	{
		static float startXPos;
		static float startYPos;
		static const Vector2& resolution{ Core::GetInstance().GetResolution() };

		if (KeyManager::GetInstance().GetKeyDown(Key::LBUTTON))
		{
			const Vector2& mousePos{ KeyManager::GetInstance().GetMousePos() };

			startXPos = mousePos.X;
			startYPos = mousePos.Y;
		}
		else if (KeyManager::GetInstance().GetKeyUp(Key::LBUTTON))
		{
			const Vector2& mousePos{ KeyManager::GetInstance().GetMousePos() };

			float endXPos{ mousePos.X };
			float endYPos{ mousePos.Y };

			CreateTileAtMouseDrag(startXPos, startYPos, endXPos, endYPos, isWall);
		}
	}

	void SceneTool::SaveTile(const std::wstring& path) const
	{
		std::wofstream out{ path, std::ios::binary };

		if (!out.is_open())
		{
			std::wcout << "Can Not Open File Path: " << path << std::endl;
			return;
		}

		TileRectangle::SaveFile(out);
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

	// TILE Count Windows Proc
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
