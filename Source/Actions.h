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

enum class GameState
{
	INVALID = -1,
	MAIN,
	GAMEOVER
};

extern std::atomic<GameAction> game_action;
extern std::atomic<GameState> game_state;