//Thomas Gilman
//ETEC2110
//51
//Lab 9 program 1
#include "stdafx.h"
#include "BlockHead.h"


BlockHead::BlockHead(SDL_Window *window, SDL_Renderer *renderer)
{
	if ((font = TTF_OpenFont("C:\\Users\\Thoma\\OneDrive\\Documents\\programs\\SystemsProg\\Lab 9\\BlockHeadsC++\\resources\\cubicblock.ttf", 50)) == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not Open Font: %s\n", TTF_GetError());
		SDL_Delay(5000);
	}
	// load support for the JPG and PNG image formats
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags) 
		printf("IMG_Init failed :%s\n", IMG_GetError());

	image = IMG_Load("C:\\Users\\Thoma\\OneDrive\\Documents\\programs\\SystemsProg\\Lab 9\\BlockHeadsC++\\resources\\creepy.jpg");
	if (image == NULL)
		printf("Could not loag image: %s\n", IMG_GetError());
	BlockHeadTexture = SDL_CreateTextureFromSurface(renderer, image);

	MessageRect->x = 0; MessageRect->y = 0; MessageRect->w = 200; MessageRect->h = 50;	//Set Message Rectangle for NumHead Count
	srand(time(0));																		//Seed Random
	SDL_FreeSurface(surface); surface = SDL_GetWindowSurface(window);					//Free Surface and set it for color format

	for (int index = 0; index < listSize; index++)
	{
		BLOCKHEAD newHead;
		newHead.x = rand() % SCREEN_WIDTH; newHead.y = rand() % SCREEN_HEIGHT;							//random Position
		newHead.dx = ((float)rand() / RAND_MAX) * 1; newHead.dy = ((float)rand() / RAND_MAX) * 1;		//random speed
		newHead.size = (rand() % 10) + 10;																//random size between 10 and 20
		newHead.color = SDL_MapRGBA(surface->format, rand() % 255, rand() % 255, rand() % 255, 255);	//random color
		printf("BlockHead%d, posX:%f, posY:%f, dX:%f, dY%f\n", index, newHead.x, newHead.y, newHead.dx, newHead.dy);
		blockHeadList.push_back(newHead);
	}
};
void BlockHead::moveBlockHeads()
{
	if (blockHeadList.size() > 0)
	{
		for (iter = blockHeadList.begin(); iter < blockHeadList.end(); iter++)
		{
			//check if going or outside of bounds of screen and invert directions
			if ((iter->x + iter->dx + iter->size) >= SCREEN_WIDTH)
			{
				iter->x = (SCREEN_WIDTH - iter->size);
				iter->dx = (-1 * iter->dx);
			}
			else if (iter->x + iter->dx <= 0)
			{
				iter->x = 0;
				iter->dx = (-1 * iter->dx);
			}
			if ((iter->y + iter->dy + iter->size) >= SCREEN_HEIGHT)
			{
				iter->y = (SCREEN_HEIGHT - iter->size);
				iter->dy = (-1 * iter->dy);
			}
			else if (iter->y + iter->dy <= 0)
			{
				iter->y = 0;
				iter->dy = (-1 * iter->dy);
			}
			else //move Blockhead cordinates
			{
				iter->x += iter->dx; iter->y += iter->dy;
			}
		}
	}
};
void BlockHead::renderBlockHeads(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	if (blockHeadList.size() > 0)
	{
		//My pixel Variables
		pixFmt = surface->format;									//Set Color Format
		Uint8 Red, Green, Blue, Alpha;								//Get UINT8 Colors from UINT32

		for (iter = blockHeadList.begin(); iter < blockHeadList.end(); iter++)
		{
			SDL_GetRGBA(iter->color, pixFmt, &Red, &Green, &Blue, &Alpha); //Get BlockHeads RGBA

			SDL_Rect HeadRect;

			HeadRect.x = iter->x; HeadRect.y = iter->y;					//setposition of Head rectangle
			HeadRect.h = iter->size; HeadRect.w = iter->size;			//set dimension
			SDL_SetRenderDrawColor(renderer, Red, Green, Blue, Alpha);	//set Rect color
			SDL_RenderFillRect(renderer, &HeadRect);					//Color blockhead rect
			SDL_RenderDrawRect(renderer, &HeadRect);

			//display image on rectangle
			
			SDL_RenderCopy(renderer, BlockHeadTexture, NULL, &HeadRect);
		}
		//Display Number of BlockHeads in font
		sprintf_s(stringBuff, "blocks:%d", blockHeadList.size());			//convert int to string to be displayed
		SDL_FreeSurface(textSurface);										//always free befor re writing to
		textSurface = TTF_RenderText_Solid(font, stringBuff, fontColor);	//Text for numBlockheads
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);		//Create texture to apply to transparent rectangle
		SDL_RenderCopy(renderer, texture, NULL, MessageRect);
		SDL_DestroyTexture(texture);										//destroy texturer after applying to free for use
	}
};
void BlockHead::addBlockHeads(int numOfHeads, int mousePosX, int mousePosY)
{
	int prevSize = listSize;
	listSize += numOfHeads;

	while (numOfHeads--)
	{
		BLOCKHEAD newHead;
		if (mousePosX != NULL && mousePosY != NULL)
		{
			newHead.x = mousePosX; newHead.y = mousePosY;												//Adding Node at specific location
		}
		else
		{
			newHead.x = rand() % SCREEN_WIDTH; newHead.y = rand() % SCREEN_HEIGHT;						//random Position
		}
		newHead.dx = ((float)rand() / RAND_MAX) * 1; newHead.dy = ((float)rand() / RAND_MAX) * 1;		//random speed
		newHead.size = (rand() % 10) + 10;																//random size between 10 and 20
		newHead.color = SDL_MapRGBA(surface->format, rand() % 255, rand() % 255, rand() % 255, 255);	//random color
		printf("BlockHead:%d, posX:%f, posY:%f, dX:%f, dY%f\n", prevSize++, newHead.x, newHead.y, newHead.dx, newHead.dy);
		blockHeadList.insert(blockHeadList.end(),newHead);
	}
};
void BlockHead::deleteBlockHeads(int mousePosX, int mousePosY)
{
	if (blockHeadList.size() > 0)
	{
		int ranKill, numHead = 0;
		for (int index = 0; index < listSize; index++)
		{
			++numHead;									//keep track of head count
			if (mousePosX != NULL && mousePosY != NULL)	//deleting specific nodes
			{
				if ((mousePosX >= blockHeadList[index].x) && (mousePosX <= (blockHeadList[index].x + blockHeadList[index].size)) &&
					(mousePosY >= blockHeadList[index].y) && (mousePosY <= (blockHeadList[index].y + blockHeadList[index].size)))
				{
					BLOCKHEAD temp = blockHeadList.back();		//save BLOCKHEAD at end of list
					blockHeadList.back() = blockHeadList[index];//move BLOCKHEAD being deleted to end
					blockHeadList[index] = temp;				//place saved BLOCKHEAD at index of iter
					blockHeadList.pop_back();					//remove BLOCKHEAD at end of list
					--numHead; --listSize;
				}
			}
			else if (mousePosX == NULL && mousePosY == NULL) //deleting random node
			{
				if ((ranKill = rand() % 10) == 1)		//10% chance of death
				{
					printf("Node killed: %d\n", numHead);
					BLOCKHEAD temp = blockHeadList.back();		//save BLOCKHEAD at end of list
					blockHeadList.back() = blockHeadList[index];//move BLOCKHEAD being deleted to end
					blockHeadList[index] = temp;				//place saved BLOCKHEAD at index of iter
					blockHeadList.pop_back();					//remove BLOCKHEAD at end of list
					--numHead; --listSize;
				}
			}
		}
		printf("Heads left: %d\n", numHead);
	}
	else
		printf("No heads to decapitate!");
};
void BlockHead::updateBlockHeads(SDL_Renderer *renderer)
{
	moveBlockHeads();
	renderBlockHeads(renderer);
}
//speed up all blockheads
void BlockHead::speedUpHeads()
{
	if (blockHeadList.size() > 0)
	{
		for (iter = blockHeadList.begin(); iter < blockHeadList.end(); iter++)
		{
			if ((iter->dx > 0) && (iter->dx < 1.0f))
				iter->dx += 0.01f;							//dx is above 0 add more speed
			else if((iter->dx < 0) && (iter->dx > -1.0f))
				iter->dx -= 0.01f;							//dx below 0 decrease it some more
			if ((iter->dy > 0) && (iter->dy < 1.0f))
				iter->dy += 0.01f;							//dy is above 0 add more speed
			else if((iter->dy < 0) && (iter->dy > -1.0f))
				iter->dy -= 0.01f;							//dx below 0 decrease it some more
		}
	}
};
//slow down all blockheads
void BlockHead::slowDownHeads()
{
	if (blockHeadList.size() > 0)
	{
		for (iter = blockHeadList.begin(); iter < blockHeadList.end(); iter++)
		{
			if (iter->dx < 0)
				iter->dx += 0.01f;
			else
				iter->dx -= 0.01f;
			if (iter->dy < 0)
				iter->dy += 0.01f;
			else
				iter->dy -= 0.01f;
		}
	}
};
void BlockHead::printBlockHead_Data()
{
	for (iter = blockHeadList.begin(); iter < blockHeadList.end(); iter++)
		printf("Blockhead: %d position is x: %f, y: %f, Speed is dx: %f, dy: %f\n", iter,
			iter->x, iter->y, iter->dx, iter->dy);

	printf("\n");
};
BlockHead::~BlockHead()
{
	delete(MessageRect);			//free memory for MessageRect
	TTF_Quit();						//Quit True type Font
	IMG_Quit();						//Quite SDL Image
	SDL_DestroyTexture(BlockHeadTexture);
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(image);
	printf("Freed Blockhead memory!, BlockHead class Destroyed");
};
