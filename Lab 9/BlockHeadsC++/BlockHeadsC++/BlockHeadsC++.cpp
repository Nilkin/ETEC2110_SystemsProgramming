// BlockHeadsC++.cpp : Defines the entry point for the console application.
//
//Thomas Gilman
//ETEC2110
//51
//Lab 9 program 1
#include "stdafx.h"
#include "BlockHead.h"

//SDL Variables
SDL_Window *window;					//My window
SDL_Renderer *renderer;				//my Renderer
SDL_Event sysEvent;					//myEvent Handler

int main(int argc, char * argv[])
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"SDL not initialized. SDL_ERROR : %s\n", SDL_GetError());
		SDL_Delay(5000);
		return -1;
	}
	if (TTF_Init() < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font not initialized: %s\n", TTF_GetError());
		SDL_Delay(5000);
		return -1;
	}
	window = SDL_CreateWindow("BlockHead", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Window not created: %s\n", SDL_GetError());
		SDL_Delay(5000);
		return -1;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Renderer not created: %s\n", SDL_GetError());
		SDL_Delay(5000);
		return -1;
	}


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);			//clear window
	SDL_RenderClear(renderer);

	BlockHead *myBlockHeadList = new BlockHead(window, renderer);				//BlockHead Class
	int waiting = 1, pause = 1, mousePosX = NULL, mousePosY = NULL;	//Loop variables
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

			case SDLK_a: //add some BLOCKHEADS
				myBlockHeadList->addBlockHeads();
				break;

			case SDLK_f: //speed up BLOCKHEADS
				myBlockHeadList->speedUpHeads();
				break;

			case SDLK_g: //get Blockheads pos and num
				myBlockHeadList->printBlockHead_Data();
				break;

			case SDLK_r: //Kill some BLOCKHEADS
				myBlockHeadList->deleteBlockHeads();
				break;

			case SDLK_s: //slow down the BLOCKHEADS
				myBlockHeadList->slowDownHeads();
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
						case SDLK_a: //add some BLOCKHEADS
							myBlockHeadList->addBlockHeads();
							SDL_RenderPresent(renderer);
							break;

						case SDLK_g: //get Blockheads pos and num
							myBlockHeadList->printBlockHead_Data();
							break;

						case SDLK_n:	//Next Position
							myBlockHeadList->updateBlockHeads(renderer);
							SDL_RenderPresent(renderer);
							break;

						case SDLK_r: //Kill some BLOCKHEADS
							myBlockHeadList->deleteBlockHeads();
							SDL_RenderPresent(renderer);
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

					case SDL_MOUSEBUTTONDOWN:
						switch (sysEvent.button.button)
						{
						case SDL_BUTTON_LEFT:
							SDL_GetMouseState(&mousePosX, &mousePosY);
							if ((mousePosX >= 0 && mousePosX <= SCREEN_WIDTH) && (mousePosY >= 0 && mousePosY <= SCREEN_HEIGHT)) //within boundaries of SCREEN
								myBlockHeadList->addBlockHeads(1, mousePosX, mousePosY);
							SDL_RenderPresent(renderer);
							SDL_Delay(20);
							break;
						case SDL_BUTTON_RIGHT:	//right mouse button, delete Node
							SDL_GetMouseState(&mousePosX, &mousePosY);
							if ((mousePosX >= 0 && mousePosX <= SCREEN_WIDTH) && (mousePosY >= 0 && mousePosY <= SCREEN_HEIGHT)) //within boundaries of SCREEN
								myBlockHeadList->deleteBlockHeads(mousePosX, mousePosY);
							SDL_RenderPresent(renderer);
							break;
						}
						break;
					}

				}							//UNPAUSED
				break;

			default:
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (sysEvent.button.button)
			{
			case SDL_BUTTON_LEFT:
				printf("left mouse button pressed");
				SDL_GetMouseState(&mousePosX, &mousePosY);
				if ((mousePosX >= 0 && mousePosX <= SCREEN_WIDTH) && (mousePosY >= 0 && mousePosY <= SCREEN_HEIGHT)) //within boundaries of SCREEN
					myBlockHeadList->addBlockHeads(1, mousePosX, mousePosY);
				SDL_Delay(20);
				break;

			case SDL_BUTTON_RIGHT:	//right mouse button, delete Node
				SDL_GetMouseState(&mousePosX, &mousePosY);
				if ((mousePosX >= 0 && mousePosX <= SCREEN_WIDTH) && (mousePosY >= 0 && mousePosY <= SCREEN_HEIGHT)) //within boundaries of SCREEN
					myBlockHeadList->deleteBlockHeads(mousePosX, mousePosY);
				break;
			}
			break;

		default:
			break;
		}
		myBlockHeadList->updateBlockHeads(renderer); //Move and Render BlockHeads
		SDL_RenderPresent(renderer);
	}
	//Free my variables and memory
	delete(myBlockHeadList);	//clean up memory
	//SDL_Delay(2500);			//wait a little to show consol
	SDL_Quit();					//Quit SDL subsystems

	return 0;
}