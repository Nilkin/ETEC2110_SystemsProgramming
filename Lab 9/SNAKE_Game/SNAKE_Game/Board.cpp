//Thomas Gilman
//Systems Programming
//ETEC 2110
//51
//Lab 9
//part 2 SNAKE GAME
#include "stdafx.h"
#include <time.h>
#include "Board.h"


Board::Board()
{
	srand(time(0));
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"SDL not initialized. SDL_ERROR : %s\n", SDL_GetError());
		SDL_Delay(5000);
		exit(-1);
	}
	window = SDL_CreateWindow("SNAKE_GAME!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Window not created: %s\n", SDL_GetError());
		SDL_Delay(5000);
		exit(-1);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Renderer not created: %s\n", SDL_GetError());
		SDL_Delay(5000);
		exit(-1);
	}
	if (TTF_Init() < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font not initialized: %s\n", TTF_GetError());
		SDL_Delay(5000);
		exit(-1);
	}
	const char* FontPATH = "C:\\Users\\Thoma\\OneDrive\\Documents\\programs\\SystemsProg\\Lab 9\\SNAKE_Game\\resources\\cubicblock.ttf";
	if ((font = TTF_OpenFont(FontPATH, 75)) == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not Open Font: %s\n", TTF_GetError());
		SDL_Delay(5000);
		exit(-1);
	}
	//Setup image support
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;				//load support for the JPG and PNG image formats
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags)
	{
		printf("IMG_Init failed :%s\n", IMG_GetError());
		SDL_Delay(5000);
		exit(-1);
	}
	windowRect = new(SDL_Rect);
	windowRect->x = 100; windowRect->y = 200; 
	windowRect->w = 600; windowRect->h = 75;

	mySnake = new Snake(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);					//Create Snake Class
	myApple = new Apple(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);							//Create Apple
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);								//clear window
	SDL_RenderClear(renderer);
};
void Board::updateGame()
{
	int waiting = 1, pause = 1;
	while (waiting)
	{
		SDL_PollEvent(&sysEvent);
		switch (sysEvent.type)
		{
		case SDL_KEYDOWN:
			switch (sysEvent.key.keysym.sym)
			{
			case SDL_QUIT:	//exit program
			case SDLK_ESCAPE:
			case SDLK_q:
				waiting = 0;
				break;

			case SDLK_a:	//Move left
				if (mySnake->moveSnake(myApple, renderer, sysEvent.key.keysym.sym) == false)
					waiting = 0;
				break;

			case SDLK_d:	//Move right
				if (mySnake->moveSnake(myApple, renderer, sysEvent.key.keysym.sym) == false)
					waiting = 0;
				break;

			case SDLK_w:	//Move up
				if (mySnake->moveSnake(myApple, renderer, sysEvent.key.keysym.sym) == false)
					waiting = 0;
				break;

			case SDLK_s:	//Move down
				if (mySnake->moveSnake(myApple, renderer, sysEvent.key.keysym.sym) == false)
					waiting = 0;
				break;

			case SDLK_g:	//Get Snake Positions
				mySnake->printSnake_Data();
				break;

			case SDLK_p:
				pause = 1;
				while (pause)					//PAUSED
				{
					SDL_PollEvent(&sysEvent);
					switch (sysEvent.type)
					{
					case SDL_KEYDOWN:
						switch (sysEvent.key.keysym.sym)
						{
						case SDLK_g:	//Get Snake Positions
							mySnake->printSnake_Data();
							break;

						case SDLK_p:
							pause = 0;
							break;

						case SDLK_ESCAPE:
						case SDL_QUIT:
							pause = 0;
							waiting = 0;
							break;

						default:
							break;
						}
						break;
					}
				}							//UNPAUSED
				break;

			default:	//update snake Pos even when not pressing a key
				break;
			}
			break;
		}
		if (mySnake->moveSnake(myApple, renderer) == false)
			waiting = 0;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		mySnake->renderSnake(renderer);	//Draw Snake
		myApple->drawApple(renderer);	//Draw apple
		SDL_RenderPresent(renderer);
	}
	endGame();
};
//Game is over, display snake size and ask if you want to play again
void Board::endGame()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	//Clear Window
	SDL_RenderClear(renderer);
	printf("im supposed to clear the screen!");

	sprintf_s(myString, "game over: snakesize = %d", mySnake->getSize());
	SDL_FreeSurface(gameSurface);									//always free befor re writing to
	gameSurface = TTF_RenderText_Solid(font, myString, {0, 0, 0});	//Text for numBlockheads
	gameTexture = SDL_CreateTextureFromSurface(renderer, gameSurface);
	SDL_RenderCopy(renderer, gameTexture, NULL, windowRect);
	SDL_DestroyTexture(gameTexture);
	SDL_RenderPresent(renderer);

	bool waiting = true;
	while (waiting)
	{
		SDL_PollEvent(&sysEvent);
		switch (sysEvent.type)
		{
		case SDL_KEYDOWN:
			switch (sysEvent.key.keysym.sym)
			{
			case SDL_QUIT:		//exit program
			case SDLK_ESCAPE:
			case SDLK_q:
			case SDLK_SPACE:
				waiting = false;
				break;

			case SDLK_r:		//reset program
				mySnake = new Snake(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);					//Create Snake Class
				myApple = new Apple(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);							//Create Apple
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	//clear window
				SDL_RenderClear(renderer);
				updateGame();											//return to game loop
				break;

			default:
				break;
			}
			break;
		default:
			break;
		}
	}
};
Board::~Board()
{
	delete(windowRect);
	delete(mySnake);//clean up class memory
	delete(myApple);
	TTF_Quit();		//Quit True type Font
	IMG_Quit();		//Quite SDL Image
	SDL_Quit();		//Quit SDL
};
