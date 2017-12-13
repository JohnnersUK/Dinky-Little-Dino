#include <Engine\GameTime.h>
#include <Engine\InputEvents.h>

#include "Game.h"
#include "GameFont.h"

#include "Actions.h"

#include <string>
#include <fstream>
#include <iostream>

EndlessGame::~EndlessGame()
{
	this->inputs->unregisterCallback(key_handler_id);

	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}

	if (backdrop1)
	{
		delete backdrop1;
		backdrop1 = nullptr;
	}

	if (backdrop2)
	{
		delete backdrop2;
		backdrop2 = nullptr;
	}

	if (title)
	{
		delete title;
		title = nullptr;
	}

	if (game_over)
	{
		delete game_over;
		game_over = nullptr;
	}

	platforms.reset();
}

bool EndlessGame::init()
{
	game_width = 1280;
	game_height = 720;

	if (!initAPI(ASGE::Renderer::WindowMode::WINDOWED))
	{
		return false;
	}

	renderer->setWindowTitle("Dinky little dino - A game by Oscar Johnson");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);

	this->inputs->use_threads = false;
	this->inputs->addCallbackFnc(
		ASGE::EventType::E_KEY, &EndlessGame::keyHandler, this);

	if (GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Roboto-Black.ttf", 18), "default", 42))
	{
		GameFont::fonts[0]->id = 1;
		renderer->setFont(1);
	}

	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}

	backdrop1 = renderer->createRawSprite();
	backdrop1->xPos(0);
	backdrop1->yPos(0);

	if (!backdrop1->loadTexture("..\\..\\Resources\\Textures\\BG_Game.png"))
	{
		return false;
	}

	backdrop2 = renderer->createRawSprite();
	backdrop2->xPos(1280);
	backdrop2->yPos(0);

	if (!backdrop2->loadTexture("..\\..\\Resources\\Textures\\BG_Game.png"))
	{
		return false;
	}

	title = renderer->createRawSprite();
	title->xPos(0);
	title->yPos(70);

	if (!title->loadTexture("..\\..\\Resources\\Textures\\Title.png"))
	{
		return false;
	}

	game_over = renderer->createRawSprite();
	game_over->xPos(0);
	game_over->yPos(0);

	if (!game_over->loadTexture("..\\..\\Resources\\Textures\\GameOver.png"))
	{
		return false;
	}

	player.init(renderer.get());

	int x = 0;
	std::string line;
	std::ifstream myfile("..\\..\\Resources\\scores.txt");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			score_table[x] = std::stoi(line);
			x++;
		}
		myfile.close();
	}

	high_score_table = " High Scores: ";
	for (int x = 0; x < 5; x++)
	{
		high_score_table += "\n " + std::to_string(x + 1) + ". " + std::to_string(score_table[x]);
	}
	for (int x = 5; x < 10; x++)
	{
		high_score_table2 += "\n";
		if (x + 1 == 10)
		{
			high_score_table2 += std::to_string(x + 1) + ". " + std::to_string(score_table[x]);
		}
		else
		{
			high_score_table2 += " " + std::to_string(x + 1) + ". " + std::to_string(score_table[x]);
		}
	}

	return true;
}

void EndlessGame::update(const ASGE::GameTime& us)
{
	if (game_action != GameAction::DEFAULT)
	{
		player_count += us.delta_time.count() * 00.1;
		other_count += us.delta_time.count() * 00.1;
		if (player_count > 5)
		{
			player_score++;
			if (player_score > goal)
			{
				if (game_speed > 0.2)
				{
					game_speed -= 0.1f;
					goal += 250;
				}
			}
			if (player.update(platforms))
			{
				game_action = GameAction::DEFAULT;
				game_state = GameState::GAMEOVER;
				player_end_score = player_score;
				updateScoreTable();
				restart();
			}
			player_count = 0;
		}
		if (other_count > game_speed)
		{
			updateBackdrop();
			platforms.updateBlocks();
			block_count++;
			if (block_count == 96)
			{
				platforms.getNextBlock(renderer.get());
				block_count = 0;
			}
			other_count = 0;
		}
	}
	processActions();
}

void EndlessGame::render(const ASGE::GameTime& us)
{
	std::string score_string;
	if (game_state == GameState::MAIN)
	{
		score_string = "Score: " + std::to_string(player_score);

		renderer->renderSprite(*backdrop1);
		renderer->renderSprite(*backdrop2);
		renderer->renderSprite(*title);

		renderer->renderText(score_string.c_str(), 10, 20, 1.0, ASGE::COLOURS::DARKBLUE);
		renderer->renderText(high_score_table.c_str(), score_xPos+ 100, 150, ASGE::COLOURS::DARKBLUE);
		renderer->renderText(high_score_table2.c_str(), score_xPos + 250, 150, ASGE::COLOURS::DARKBLUE);

		platforms.renderBlocks(renderer.get());
		player.render(renderer.get());
	}

	if (game_state == GameState::GAMEOVER)
	{
		std::string end_score = "Score: " + std::to_string(player_end_score);

		renderer->renderSprite(*game_over);

		if (player_end_score == score_table[0])
		{
			renderer->renderText("New high score!", 900, 400, 1.0, ASGE::COLOURS::DARKRED);
		}

		renderer->renderText(end_score.c_str(), 900, 430, 1.0, ASGE::COLOURS::DARKRED);
		renderer->renderText("- Press any key -", 900, 460, 1.0, ASGE::COLOURS::DARKRED);
	}

}

void EndlessGame::keyHandler(const ASGE::SharedEventData data)
{
	const ASGE::KeyEvent* key_event = 
		static_cast<const ASGE::KeyEvent*>(data.get());
	
	auto key = key_event->key;
	auto action = key_event->action;

	if (key == ASGE::KEYS::KEY_ESCAPE)
	{
		signalExit();
	}

	if (action == ASGE::KEYS::KEY_PRESSED)
	{
		if (game_state == GameState::MAIN)
		{
			if (key == ASGE::KEYS::KEY_UP)
			{
				game_action = GameAction::JUMP;
			}
			if (key == ASGE::KEYS::KEY_LEFT)
			{
				game_action = GameAction::LEFT;
			}
			if (key == ASGE::KEYS::KEY_RIGHT)
			{
				game_action = GameAction::RIGHT;
			}
			if (key == ASGE::KEYS::KEY_SPACE)
			{
				game_action = GameAction::KICK;
			}
		}
		else if (game_state == GameState::GAMEOVER)
		{
			game_state = GameState::MAIN;
		}
	}

	if (action == ASGE::KEYS::KEY_RELEASED)
	{
		if (game_state == GameState::MAIN)
		{
			if (key == ASGE::KEYS::KEY_LEFT || key == ASGE::KEYS::KEY_RIGHT)
			{
				game_action = GameAction::STOP;
			}
		}
	}
}

void EndlessGame::processActions()
{
	player.move();
}

void EndlessGame::updateBackdrop()
{
	backdrop1->xPos(backdrop1->xPos() - 1);
	backdrop2->xPos(backdrop2->xPos() - 1);
	title->xPos(title->xPos() - 2);
	score_xPos -= 2;

	if (backdrop1->xPos() == -1280)
	{
		backdrop1->xPos(1280);
	}
	if (backdrop2->xPos() == -1280)
	{
		backdrop2->xPos(1280);
	}

}

void EndlessGame::updateScoreTable()
{
	int new_score = player_score;
	int old_score = 0;

	for (int x = 0; x < 10; x++)
	{
		if (new_score > score_table[x])
		{
			old_score = score_table[x];
			score_table[x] = new_score;
			new_score = old_score;
		}
	}

	std::ofstream myfile("..\\..\\Resources\\scores.txt");
	if (myfile.is_open())
	{
		for (int x = 0; x < 10; x++)
		{
			myfile << std::to_string(score_table[x]) << "\n";
		}
		myfile.close();
	}

}

void EndlessGame::restart()
{
	player_count = 0.0f;
	other_count = 0.0f;

	game_speed = 1;
	goal = 250;

	block_count = 0;
	player_score = 0;

	backdrop1->xPos(0);
	backdrop1->yPos(0);

	backdrop2->xPos(1280);
	backdrop2->yPos(0);

	title->xPos(0);
	title->yPos(70);

	int x = 0;
	std::string line;
	std::ifstream myfile("..\\..\\Resources\\scores.txt");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			score_table[x] = std::stoi(line);
			x++;
		}
		myfile.close();
	}


	high_score_table = " High Scores: ";
	high_score_table2 = "";
	for (int x = 0; x < 5; x++)
	{
		high_score_table += "\n " + std::to_string(x + 1) + ". " + std::to_string(score_table[x]);
	}
	for (int x = 5; x < 10; x++)
	{
		high_score_table2 = high_score_table2 + "\n";
		if (x + 1 == 10)
		{
			high_score_table2 += std::to_string(x + 1) + ". " + std::to_string(score_table[x]);
		}
		else
		{
			high_score_table2 += " " + std::to_string(x + 1) + ". " + std::to_string(score_table[x]);
		}
	}

	player.reset();
	platforms.reset();
}


