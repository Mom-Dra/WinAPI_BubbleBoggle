#include "CommandManager.h"

namespace MomDra
{
	void CommandManager::Execute(std::unique_ptr<Command> command)
	{
		command->Execute();
		undoStack.emplace(std::move(command));
		
		while (!redoStack.empty())
		{
			redoStack.pop();
		}
	}

	void CommandManager::Undo()
	{
		if (undoStack.empty()) return;

		undoStack.top()->Undo();
		redoStack.emplace(std::move(undoStack.top()));
		undoStack.pop();
	}

	void CommandManager::Redo()
	{
		if (redoStack.empty()) return;

		redoStack.top()->Execute();
		undoStack.emplace(std::move(redoStack.top()));
		redoStack.pop();
	}
}