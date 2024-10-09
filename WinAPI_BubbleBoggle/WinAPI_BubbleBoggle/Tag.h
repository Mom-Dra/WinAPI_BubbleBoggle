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
		LAST
	};

	enum class BrushType
	{
		HOLLOW,
		LAST
	};

	enum class PenType
	{
		RED,
		GREEN,
		BLUE,
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
		STAGE_01,
		STAGE_02,
		LAST
	};
}
