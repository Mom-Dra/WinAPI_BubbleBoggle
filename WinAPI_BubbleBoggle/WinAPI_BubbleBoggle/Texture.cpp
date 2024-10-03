#include "Texture.h"
#include "Core.h"

using namespace MomDra;

Texture::Texture(const std::wstring& filePath) noexcept
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
	// ���Ϸ� ���� �ε��� �����͸� ��Ʈ������ ����
	hBit = static_cast<HBITMAP>(LoadImage(nullptr, filePath.data(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE));

	// ��Ʈ�ʰ� ������ DC
	hdc = CreateCompatibleDC(Core::GetInstance().GetMainDC());
	HBITMAP hOldBit = static_cast<HBITMAP>(SelectObject(hdc, hBit));
	DeleteObject(hOldBit);

	// ���� ���� ����
	BITMAP bitInfo;
	GetObject(hBit, sizeof(BITMAP), &bitInfo);
}
