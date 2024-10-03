#pragma once
#include <memory>
#include <array>
#include "Tag.h"
#include "framework.h"
#include "Scene.h"

namespace MomDra
{
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

		inline void Update() const noexcept
		{
			currScene->Update();
		}

		inline void Render(const HDC& hdc) const noexcept
		{
			currScene->Render(hdc);
		}

	private:
		explicit SceneManager() noexcept = default;
		explicit SceneManager(const SceneManager& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
	};
}
