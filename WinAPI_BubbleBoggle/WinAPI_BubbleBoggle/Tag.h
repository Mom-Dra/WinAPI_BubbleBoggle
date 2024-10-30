#pragma once

namespace MomDra
{
	enum class Layer
	{
		Default,
		Player,
		Monster,
		Projectile,
		Tile,
		Ground,
		Wall,
		Item,
		UI,
		Last
	};

	enum class BrushType
	{
		Hollow,
		Last
	};

	enum class PenType
	{
		Red,
		Green,
		Blue,
		Orange,
		Last
	};

	enum class EventType
	{
		CreateObject,
		DeleteObject,
		ChangeScene,
		Last
	};

	enum class SceneType
	{
		Tool,
		Start,
		Intro,
		Stage1,
		Stage2,
		GameOver,
		GameWin,
		Last
	};
}
