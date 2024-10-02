#pragma once
#include "framework.h"
#include <string>
#include "Vector2.h"

using namespace CK;

class Object
{
private:
	Vector2 pos;
	Vector2 scale;

public:
	explicit Object() noexcept = default;
	explicit Object(const Vector2& pos, const Vector2& scale) noexcept;
	virtual ~Object() noexcept = default;

	void SetPos(Vector2 pos) noexcept;
	void SetScale(Vector2 scale) noexcept;

	const Vector2& GetPos() const noexcept;
	const Vector2& GetScale() const noexcept;

	virtual void Update() noexcept = 0;
	virtual void Render(const HDC& hdc) const noexcept = 0;
};
