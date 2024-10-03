#include "Texture.h"

Texture::~Texture()
{
	DeleteDC(hdc);
	DeleteObject(bit);
}

void Texture::Load(const std::wstring& filePath)
{
	bit = static_cast<HBITMAP>(LoadImage(nullptr, filePath.data(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE));
}
