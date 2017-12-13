#pragma once
#include <Engine\Sprite.h>
#include <Engine\Renderer.h>
#include <vector>

class Platforms
{
public:
	Platforms();
	~Platforms();

	void getNextBlock(ASGE::Renderer *renderer);
	ASGE::Sprite* createBlock(ASGE::Renderer *renderer);
	void renderBlocks(ASGE::Renderer *renderer);
	void updateBlocks();

	int getSize();
	int getBlockX(int size);
	int getBlockY(int size);

	void reset();

private:
	std::vector<ASGE::Sprite*> blocks;

	int size = 0;
	float current_height = 6.5;
	
	bool new_block;

};
