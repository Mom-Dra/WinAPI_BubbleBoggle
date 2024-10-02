#pragma once
#include <memory>
#include <array>
#include "Tag.h"

class Scene;

enum class SceneType
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,
	LAST
};

class SceneManager
{
private:
	std::array<std::unique_ptr<Scene>, static_cast<int> (SceneType::LAST)> Scenes;
	Scene* currScene{ nullptr };

public:
	static SceneManager& GetInstance() noexcept;

	void Initialize() noexcept;

private:
	explicit SceneManager() noexcept = default;
	explicit SceneManager(const SceneManager& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
};
