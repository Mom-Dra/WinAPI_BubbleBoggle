#pragma once
#include "framework.h"
#include "Res.h"

class Texture : public Res
{
private:
	HDC hdc;
	HBITMAP hBit;
	BITMAP bitInfo;

public:
	explicit Texture(const std::wstring& filePath) noexcept;
	~Texture();

	inline int GetWidth() const noexcept { return bitInfo.bmWidth; }
	inline int GetHeight() const noexcept { return bitInfo.bmHeight; }
	inline const HDC& GetDC() const noexcept { return hdc; }

private:
	void Load(const std::wstring& filePath);
};
