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

	enum class MonsterState
	{
		IDLE,
		PATROL,
		TRACE,
		ATTACK,
		RUN,
		DEAD,
		LAST
	};

	enum class PlayerState
	{
		IDLE,
		WALK,
		JUMP,
		ATTACK,
		HIT,
		DEAD,
		LAST
	};

	enum class PlayerAttackState
	{
		NORMAL_ATTACK1,
		NORMAL_ATTACK2,
		LAST
	};
}
