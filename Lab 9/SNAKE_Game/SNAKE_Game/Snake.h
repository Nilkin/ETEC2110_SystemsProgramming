//Thomas Gilman
//Systems Programming
//ETEC 2110
//51
//Lab 9
//part 2 SNAKE GAME
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include "Apple.h"

using namespace std;

#pragma once
class Snake
{
public:
	Snake(SDL_Window *window, SDL_Renderer *renderer, int gameWidth, int gameHeight);
	bool moveSnake(Apple *appleToEat, SDL_Renderer *renderer, SDL_Keycode sysEvent = NULL);
	int getSize();
	void renderSnake(SDL_Renderer *renderer);
	void growSnake();
	void printSnake_Data();
	~Snake();
private:
	struct BODY
	{
		float x, y;			//position
		int direction = 0, direction2 = 0;	//0 = stationary, 1 = right, 2 = down, 3 = left, 4 = up
		float speed = .1;	//SnakeSpeed
		long color;			//UINT32 Color pattern
		int size = 25;		//movement and size component
	};
	std::vector<BODY> SnakeList;				//dynamic array for SnakeBody struct
	std::vector<BODY>::iterator iter;			//my Vector iterator
	SDL_Surface *snakeSurface;					//surface for getting pixel format and image
	SDL_Texture *snakeTexture;					//Texture for SnakeBody
	SDL_PixelFormat *pixFmt;					//my Pixel Format specifier
	SDL_Keycode lastKeyPressed;					//Set moving right to default
	int bodySize = 5;							//how many body pieces of the snake there is
	int SCREEN_WIDTH, SCREEN_HEIGHT;
};

