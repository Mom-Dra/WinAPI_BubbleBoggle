#include "Object.h"

Object::Object(const Vector2& pos, const Vector2& scale) noexcept : pos{ pos }, scale{ scale }
{

}

void Object::SetPos(Vector2 pos) noexcept
{
	this->pos = pos;
}

void Object::SetScale(Vector2 scale) noexcept
{
	this->scale = scale;
}

const Vector2& Object::GetPos() const noexcept
{
	return pos;
}

const Vector2& Object::GetScale() const noexcept
{
	return scale;
}
