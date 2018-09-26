//Thomas Gilman
//Systems Programming
//ETEC 2110
//51
//Lab 9
//part 2 SNAKE GAME
#include "SDL.h"
#include <stdlib.h>

#pragma once
class Apple
{
public:
	Apple(SDL_Renderer *renderer, int gameWidth, int gameHeight);			//allocates SDL_Rect memory and sets pos of apple
	void newApple(SDL_Renderer *renderer);	//reset pos of apple
	int getYPos();							//get YPos
	int getXPos();							//get XPos
	int getSize();							//get Size
	void drawApple(SDL_Renderer *renderer);	//fill and draw apple
	~Apple();								//deallocate memory
private:
	SDL_Rect *appleRect;
	const int appleSize = 10;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
};

