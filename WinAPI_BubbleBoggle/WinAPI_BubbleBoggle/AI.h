#pragma once
#include "Monster.h"
#include <unordered_map>
#include <string>
#include "AIState.h"

namespace MomDra
{
	/*class AI
	{
	private:
		std::array<std::unique_ptr<AIState>, static_cast<int>(MonsterState::LAST)> states;
		AIState* currState;
		Monster* owner;

	public:
		explicit AI();

		void Update();

		void AddState(std::unique_ptr<AIState> state);
		AIState* GetState(const MonsterState& monsterState) const noexcept { return states[static_cast<int>(monsterState)].get(); }
	};*/
}
