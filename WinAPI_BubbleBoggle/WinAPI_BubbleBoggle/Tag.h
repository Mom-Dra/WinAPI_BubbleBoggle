#pragma once

namespace MomDra
{
	enum class Layer
	{
		DEFAULT,
		PLAYER,
		MONSTER,
		PROJECTILE,
		TILE,
		GROUND,
		WALL,
		ITEM,
		UI,
		LAST
	};

	enum class BrushType
	{
		HOLLOW,
		LAST
	};

	enum class PenType
	{
		Red,
		Green,
		Blue,
		Orange,
		LAST
	};

	enum class EventType
	{
		CREATEOBJECT,
		DELETEOBJECT,
		CHANGESCENE,
		LAST
	};

	enum class SceneType
	{
		TOOL,
		START,
		INTRO,
		STAGE_1,
		STAGE_2,
		GAME_OVER,
		LAST
	};
}
