#pragma once
#include <string>
#include <atomic>

enum class GameAction
{
	INVALID = -1,
	NONE = 0,
	JUMP,
	LEFT,
	RIGHT,
	STOP,
	KICK,
	EXIT
};

extern std::atomic<GameAction> game_action;