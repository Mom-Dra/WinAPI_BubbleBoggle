#pragma once
#include "ImageObject.h"

class Player : public ImageObject
{
public:
	using ImageObject::ImageObject;

	virtual void Update() noexcept override;
	virtual void Render(const HDC& hdc) const noexcept override;
};
