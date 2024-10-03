#pragma once
#include "framework.h"
#include "Res.h"

class Texture : public Res
{
private:
	HDC hdc;
	HBITMAP bit;

public:
	~Texture();
	void Load(const std::wstring& filePath);
};
