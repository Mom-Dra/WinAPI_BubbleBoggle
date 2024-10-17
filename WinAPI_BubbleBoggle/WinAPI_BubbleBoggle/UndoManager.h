#pragma once

#include <stack>
#include <memory>
#include "TileRectangle.h"
#include "Scene.h"

namespace MomDra
{
	class Scene;

	class Command
	{
	public:
		virtual ~Command() = default;

		virtual void Execute() = 0;
		virtual void Undo() = 0;
	};

	class AddTileCommand : public Command
	{
	private:
		Scene* scene;
		TileRectangle::TileInfo tileInfo;
		TileRectangle* addedTile;

	public:
		inline explicit AddTileCommand(Scene* scene, const TileRectangle::TileInfo& tileInfo) noexcept : scene{ scene }, tileInfo{ tileInfo }, addedTile{ nullptr }
		{

		}

		inline void Execute() override
		{
			auto tileUniqPtr{ std::make_unique<TileRectangle>(TileRectangle::GetRealTilePos(tileInfo.pos), tileInfo.scale, Layer::TILE) };
			addedTile = tileUniqPtr.get();
			scene->AddObject(std::move(tileUniqPtr));

			TileRectangle::AddTile(tileInfo);
		}

		inline void Undo() override
		{
			scene->DeleteTile(addedTile);
			addedTile = nullptr;

			TileRectangle::RemoveTile(tileInfo);
		}
	};

	class CommandManager
	{
	private:
		static inline std::stack<std::unique_ptr<Command>> undoStack;
		static inline std::stack<std::unique_ptr<Command>> redoStack;
		static inline std::unique_ptr<Command> currentState;

	private:
		explicit CommandManager() noexcept = default;
		explicit CommandManager(const CommandManager& other) = delete;
		CommandManager& operator=(const CommandManager& other) = delete;

	public:
		static void Execute(std::unique_ptr<Command> command);
		static void Undo();
		static void Redo();
	};
}