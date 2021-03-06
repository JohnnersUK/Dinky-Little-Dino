#pragma once
#include <atomic>
#include <Engine\OGLGame.h>
#include <Engine\Sprite.h>

#include "PlayerDino.h"
#include "Platforms.h"

namespace ASGE {
	struct GameTime;
}

/**
*  EndlessGame is the main entrypoint into the game.
*  It is based on the ASGE framework and makes use of
*  the OGLGame class. This allows the rendering and
*  input initialisation to be handled easily and without
*  fuss. The game logic responsible for updating and 
*  rendering the game starts here. 
*/
class EndlessGame : 
	public ASGE::OGLGame
{
public:

	/**
	*  Default constructor for game.
	*/
	EndlessGame() = default;
	
	/**
	*  Destructor for game.
	*  Make sure to clean up any dynamically allocated
	*  memory inside the game's destructor. For example
	*  game fonts need to be deallocated. 
	*/
	~EndlessGame();

	/**
	*  The initialisation of the game.
	*  Both the game's initialisation and the API setup
	*  should be performed inside this function. Once the 
	*  API is up and running the input system can register
	*  callback functions when certain events happen. 
	*/
	virtual bool init() override;

private:
	/**
	*  The simulation for the game.
	*  The objects in the game need to updated or simulated
	*  over time. Use this function to decouple the render
	*  phases from the simulation.
	*  @param us The delta time between frames and running time
	*  @see GameTime
	*/
	virtual void update(const ASGE::GameTime & us) override;
	
	/**
	*  The rendering of the game.
	*  This function gets called after the game world has 
	*  been updated. Ensure all your objects are in a sane
	*  simulated state before calling this function.
	*  @param us The delta time between frames and running time
	*  @see GameTime
	*/
	virtual void render(const ASGE::GameTime & us) override;
	
	/**
	*  The key handling function for the game.
	*  Key inputs will be delivered and handled within this function.
	*  Make a decision whether to process the input immediately
	*  or whether to generate a queue of actions that are then
	*  processed at the beginning of the game update loop.
	*  @param data They key event and its related data. 
	*  @see SharedEventData
	*/
	void keyHandler(ASGE::SharedEventData data);

	void processActions();

	void updateBackdrop();

	void updateScoreTable();

	void restart();

private:
	int key_handler_id = -1;  /**< Input Callback ID. The callback ID assigned by the game engine. */
	ASGE::Sprite* backdrop1;
	ASGE::Sprite* backdrop2;
	ASGE::Sprite* title;
	ASGE::Sprite* game_over;
	
	PlayerDino player;
	Platforms platforms;

	std::string high_score_table = "High Scores: ";
	std::string high_score_table2;

	float player_count = 0.0f;
	float other_count = 0.0f;
	int block_count = 0;

	float game_speed = 1;
	int goal = 250;

	int player_score = 0;
	int player_end_score = 0;
	int score_table[9];
	int score_xPos = 0;
};