//Thomas Gilman
//Systems Programming
//ETEC 2110
//51
//Lab 9
//part 2 SNAKE GAME
#include "stdafx.h"
#include "Apple.h"

//Create a appleRectangle
Apple::Apple(SDL_Renderer *renderer, int gameWidth, int gameHeight)
{
	SCREEN_WIDTH = gameWidth; SCREEN_HEIGHT = gameHeight;

	appleRect = new SDL_Rect();							//allocate memory for apple
	appleRect->x = (rand() % SCREEN_WIDTH - 15) + 5;	//random XPosition
	appleRect->y = (rand() % SCREEN_HEIGHT - 15) + 5;	//random YPosition
	appleRect->w = appleSize; appleRect->h = appleSize;	//Set size
}
//change apples position
void Apple::newApple(SDL_Renderer *renderer)
{
	appleRect->x = (rand() % SCREEN_WIDTH-15) + 5;		//random XPosition
	appleRect->y = (rand() % SCREEN_HEIGHT-15) + 5;		//random YPosition
};
int Apple::getXPos()
{
	return appleRect->x;
};
int Apple::getYPos()
{
	return appleRect->y;
};
int Apple::getSize()
{
	return appleSize;
};
//Draw the apple
void Apple::drawApple(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, appleRect);
};
//Deallocate memory
Apple::~Apple()
{
	delete(appleRect);									//free appleRect memory
}
