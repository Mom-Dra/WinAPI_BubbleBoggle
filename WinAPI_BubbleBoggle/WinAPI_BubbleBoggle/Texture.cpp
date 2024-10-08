#include "Texture.h"
#include "Core.h"
#include <iostream>

namespace MomDra
{
	Texture::Texture(const std::wstring& filePath) noexcept : Res{ filePath }
	{
		Load(filePath);
	}

	Texture::~Texture()
	{
		DeleteDC(hdc);
		DeleteObject(hBit);
	}

	void Texture::Load(const std::wstring& filePath)
	{
		// 파일로 부터 로딩한 데이터를 비트맵으로 생성
		hBit = static_cast<HBITMAP>(LoadImage(nullptr, filePath.data(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE));

		// 비트맵과 연결할 DC
		hdc = CreateCompatibleDC(Core::GetInstance().GetMainDC());
		HBITMAP hOldBit = static_cast<HBITMAP>(SelectObject(hdc, hBit));
		DeleteObject(hOldBit);

		// 가로 세로 길이
		GetObject(hBit, sizeof(BITMAP), &bitInfo);
	}
}
