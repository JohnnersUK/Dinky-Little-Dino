#pragma once
#include <string>
#include <atomic>

enum class GameAction
{
	INVALID = -1,
	DEFAULT = 0,
	NONE,
	JUMP,
	LEFT,
	RIGHT,
	STOP,
	KICK,
	EXIT
};

extern std::atomic<GameAction> game_action;