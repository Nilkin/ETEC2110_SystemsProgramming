// Final1.cpp : Defines the entry point for the console application.
//
//Thomas Gilman
//ETEC2110
//51
//Finale Exam
//Problems 12 and 13
//littleFaces

#include "stdafx.h"
#include "SDL.h"

#include <time.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FACE_SIZE 50

//SDL Variables
SDL_Window *window;					//My window
SDL_Renderer *renderer;				//my Renderer
SDL_Event sysEvent;					//myEvent Handler

typedef struct littleFace
{
	int x, y;
	int direction = 1;
	int timesHit = 10;
};

void makeFace(littleFace *face)
{
	face->x = (rand() % SCREEN_WIDTH-150)+55; face->y = (rand() % SCREEN_HEIGHT-100);
	face->direction = 1;
}



int main(int argc, char * argv[])
{
	srand(time(0));
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"SDL not initialized. SDL_ERROR : %s\n", SDL_GetError());
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

	

	//rectangle items for program
	littleFace* littleFaces = (littleFace*)malloc(sizeof(littleFace));
	SDL_Rect rightColumn, leftColumn;

	makeFace(littleFaces);

	leftColumn.x = 0; leftColumn.y = 0;
	leftColumn.w = 50; leftColumn.h = SCREEN_HEIGHT;

	rightColumn.x = SCREEN_WIDTH - 50; rightColumn.y = 0;
	rightColumn.w = 50; rightColumn.h = SCREEN_HEIGHT;

	int waiting = 1, numFaces = 1;
	while (waiting)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);			//clear window
		SDL_RenderClear(renderer);

		SDL_PollEvent(&sysEvent);
		switch (sysEvent.type)
		{
		case SDL_KEYDOWN:
			switch (sysEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:	//EXIT
				waiting = 0;
				break;
			case SDLK_SPACE:	//add face
				++numFaces;
				littleFaces = (littleFace*)realloc(littleFaces, numFaces*(sizeof(littleFace)));
				makeFace(&littleFaces[numFaces - 1]);
				break;
			case SDLK_r:
				for (int index = 0; index < numFaces; index++)
				{
					printf("x:%d,y:%d,speed:%d\n", littleFaces[index].x, littleFaces[index].y, littleFaces[index].direction);
				}
			}
			break;
		}
		for (int Face = 0; Face < numFaces; Face++)	//go through list of faces
		{
			if (littleFaces[Face].x <= 50 || ((littleFaces[Face].x + FACE_SIZE) >= (SCREEN_WIDTH - FACE_SIZE)))
			{
				littleFaces[Face].direction *= -1;
				if(littleFaces[Face].direction == -1)
					SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
				else
					SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
				littleFaces[Face].timesHit--;
			}
			if (Face != 0 && littleFaces[Face].timesHit == 0)
			{
				for (int offset = 0; offset < numFaces - Face - 2; offset++)
				{
					if (numFaces != 1)
					{
						littleFaces[Face + offset] = littleFaces[Face + offset + 1]; //Move Blockhead at index to end of list
						--numFaces;
					}
				}
				
				littleFaces = (littleFace*)realloc(littleFaces, numFaces*(sizeof(littleFace)));
			}
			littleFaces[Face].x = littleFaces[Face].x + littleFaces[Face].direction;	//move
			//draw
			SDL_Rect faceToDraw;
			faceToDraw.x = littleFaces[Face].x; faceToDraw.y = littleFaces[Face].y;
			faceToDraw.h = FACE_SIZE; faceToDraw.w = FACE_SIZE;
			SDL_RenderFillRect(renderer, &faceToDraw);
			SDL_RenderDrawRect(renderer, &faceToDraw);
		}
		//columns
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &rightColumn);
		SDL_RenderFillRect(renderer, &leftColumn);
		SDL_RenderDrawRect(renderer, &rightColumn);
		SDL_RenderDrawRect(renderer, &leftColumn);

		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(window);			//destroy Window
	SDL_DestroyRenderer(renderer);		//destroy renderer
	SDL_Quit();
	free(littleFaces);
    return 0;
}

