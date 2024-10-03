#pragma once
#include "Object.h"
#include "Tag.h"
#include <vector>
#include <memory>
#include <array>
#include <string>

class Scene
{
private:
	std::array<std::vector<std::unique_ptr<Object>>, static_cast<int>(Tag::LAST)> objects;
	std::wstring sceneName;

public:
	explicit Scene() noexcept = default;
	virtual ~Scene() noexcept = default;

	inline const std::wstring& GetName() { return sceneName; }
	inline void SetName(const std::wstring& sceneName) noexcept { this->sceneName = sceneName; }

	virtual void Enter() noexcept = 0;
	virtual void Exit() noexcept = 0;

	void Update() const noexcept;
	void Render(const HDC& hdc) const noexcept;

protected:
	inline void AddObject(Object* obj, Tag type) noexcept { objects[static_cast<int>(type)].emplace_back(obj); }
};
