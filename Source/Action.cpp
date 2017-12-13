#include "Actions.h"

std::atomic<GameAction> game_action = GameAction::DEFAULT;
std::atomic<GameState> game_state = GameState::MAIN;