#include <stdio.h>
#include <stdlib.h>
#include "BlockHeadFunctions.h"

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
	/*if (TTF_Init() < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font not initialized: %s\n", TTF_GetError());
		SDL_Delay(5000);
		return -1;
	}
	if ((font = TTF_OpenFont("C:\\Users\\Thoma\\OneDrive\\Documents\\programs\\SystemsProg\\Lab 8\\BlockHead\\BlockHead\\cubicblock.ttf", 50)) == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not Open Font: %s\n", TTF_GetError());
		SDL_Delay(5000);
		return -1;
	}*/
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

	struct BLOCKHEAD_NODE *blockHeadList = initBlockHeadList();		//Initialize BlockHeadList
	int waiting = 1, pause = 1, mousePosX = NULL, mousePosY = NULL;	//Set Variables
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
				printf("%p", blockHeadList);
				addMoreHeads(blockHeadList);
				break;

			case SDLK_f: //speed up BLOCKHEADS
				speedHeads(blockHeadList);
				break;

			case SDLK_g: //get Blockheads pos and num
				getBlockHeads(blockHeadList);
				break;

			case SDLK_r: //Kill some BLOCKHEADS
				decapitateSomeHeads(blockHeadList);
				break;

			case SDLK_s: //slow down the BLOCKHEADS
				slowHeads(blockHeadList);
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
							printf("%p", blockHeadList);
							addMoreHeads(blockHeadList);
							SDL_RenderPresent(renderer);
							break;

						case SDLK_g: //get Blockheads pos and num
							getBlockHeads(blockHeadList);
							break;

						case SDLK_n:	//Next Position
							updateBlockHeadList(blockHeadList);
							SDL_RenderPresent(renderer);
							break;

						case SDLK_r: //Kill some BLOCKHEADS
							decapitateSomeHeads(blockHeadList);
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
								addMoreHeads(blockHeadList, 1, mousePosX, mousePosY);
							SDL_RenderPresent(renderer);
							SDL_Delay(20);
							break;
						case SDL_BUTTON_RIGHT:	//right mouse button, delete Node
							SDL_GetMouseState(&mousePosX, &mousePosY);
							if ((mousePosX >= 0 && mousePosX <= SCREEN_WIDTH) && (mousePosY >= 0 && mousePosY <= SCREEN_HEIGHT)) //within boundaries of SCREEN
								decapitateSomeHeads(blockHeadList, mousePosX, mousePosY);
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
					addMoreHeads(blockHeadList, 1, mousePosX, mousePosY);
				SDL_Delay(20);
				break;

			case SDL_BUTTON_RIGHT:	//right mouse button, delete Node
				SDL_GetMouseState(&mousePosX, &mousePosY);
				if ((mousePosX >= 0 && mousePosX <= SCREEN_WIDTH) && (mousePosY >= 0 && mousePosY <= SCREEN_HEIGHT)) //within boundaries of SCREEN
					decapitateSomeHeads(blockHeadList, mousePosX, mousePosY);
				break;
			}
			break;

		default:
			break;
		}
		updateBlockHeadList(blockHeadList); //Move and Render BlockHeads
		SDL_RenderPresent(renderer);
	}
	//Free my variables and memory
	deAllocateMemory(blockHeadList);//clean up memory
									//SDL_Delay(2500);					//wait a little to show consol
	TTF_Quit();							//Quit True type Font
	SDL_Quit();							//Quit SDL subsystems

	return 0;
}
