//Thomas Gilman
//Systems Programming
//ETEC 2110
//51
//Lab 9
//part 2 SNAKE GAME
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Snake.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#pragma once
class Board
{
public:
	Board();
	void updateGame();
	void endGame();
	~Board();
private:
	char myString[100];			//myString variable to display

	//SDL Variables
	SDL_Window *window;			//my window
	SDL_Renderer *renderer;		//my Renderer
	SDL_Texture *gameTexture;	//texture to apply to game surface
	SDL_Event sysEvent;			//myEvent Handler
	SDL_Surface *gameSurface;	//my Game Surface
	SDL_Rect *windowRect;		//window Rect
	TTF_Font *font;				//my Game Font

	//otherClasses
	Snake *mySnake;				//Snake Class
	Apple *myApple;				//Apple Class
};

