#pragma
#include <time.h>
#include <SDL.h>
//#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

//SDL Variables
SDL_Window *window;					//My window
SDL_Surface *surface, *textSurface;	//My surface
SDL_Surface *image;
SDL_Renderer *renderer;				//my Renderer
SDL_PixelFormat *pixFmt;			//my Pixel Format specifier
SDL_Texture *texture;				//my Texturer
SDL_Event sysEvent;					//myEvent Handler
//TTF_Font *font;
SDL_Color fontColor = { 255, 0, 0 };	//font color

//SDL_Rect *MessageRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600, listSize = 30;
char stringBuff[200];

typedef struct BLOCKHEAD_NODE
{
	float x, y;		// position				//8
	float dx, dy;	// movement component	//8
	long color;		//UINT32 Color pattern	//4
	int size;		//size between 10-20	//2
};
//Creat a BlockHeadList
struct BLOCKHEAD_NODE* initBlockHeadList()
{
	printf("Created BlockHead Nodes: %d\n", listSize);
	//MessageRect->x = 0; MessageRect->y = 0; MessageRect->w = 200; MessageRect->h = 50;								//Set Message Rectangle for NumHead Count
	srand(time(0));																									//Seed Random
	SDL_FreeSurface(surface); surface = SDL_GetWindowSurface(window);												//Free Surface and set it for color format
	struct BLOCKHEAD_NODE *HeadArray = (struct BLOCKHEAD_NODE*)malloc(listSize * sizeof(struct BLOCKHEAD_NODE));

	for(int index = 0; index < listSize ; index++)
	{
		HeadArray[index].x = rand() % SCREEN_WIDTH; HeadArray[index].y = rand() % SCREEN_HEIGHT;					//random Position
		HeadArray[index].dx = ((float)rand() / RAND_MAX) * 1; HeadArray[index].dy = ((float)rand() / RAND_MAX) * 1;	//random speed
		HeadArray[index].size = (rand() % 10) + 10;																	//random size between 10 and 20
		HeadArray[index].color = SDL_MapRGBA(surface->format, rand() % 255, rand() % 255, rand() % 255, 255);		//random color
		printf("BlockHead%d, posX:%f, posY:%f, dX:%f, dY%f\n", index, HeadArray[index].x, HeadArray[index].y, HeadArray[index].dx, HeadArray[index].dy);
	}
	printf("%p", HeadArray);
	return HeadArray;	//Return Array
};
void getBlockHeads(struct BLOCKHEAD_NODE *BlockHeadList)
{
	for (int index = 0; index < listSize; index++)
		printf("Blockhead%d position is x:%f, y:%f, Speed is dx:%f, dy:%f\n", index,
			BlockHeadList[index].x, BlockHeadList[index].y, BlockHeadList[index].dx, BlockHeadList[index].dy);

		printf("\n");
};
//Add some more Nodes to the end of the list
void addMoreHeads(struct BLOCKHEAD_NODE *blockhead_list, int numOfHeads = 10, int mousePosX = NULL, int mousePosY = NULL)
{
	SDL_FreeSurface(surface);
	surface = SDL_GetWindowSurface(window);
	int prevSize = listSize;																				//point prevSize to current listSize
	listSize = listSize + numOfHeads;																		//Change to new listSize
	printf("newlistsize: %d, prevsize: %d\n", listSize, prevSize);
	printf("%p", blockhead_list);
	if ((blockhead_list = (BLOCKHEAD_NODE*)realloc(blockhead_list, listSize * sizeof(BLOCKHEAD_NODE))) == NULL) //allocate more space
	{
		printf("Something went horribly wrong!! null blockhead pointer!!");
		exit(-1);
	}

	for (int index = prevSize; index < listSize; index++)													//add new BLOCKHEADS
	{
		BLOCKHEAD_NODE newBlockhead;																		//create New Blockhead struct
		if (mousePosX != NULL && mousePosY != NULL)
		{
			blockhead_list[index].x = mousePosX; blockhead_list[index].y = mousePosY;						//Adding Node at specific location
		}
		else
			newBlockhead.x = rand() % SCREEN_WIDTH; newBlockhead.y = rand() % SCREEN_HEIGHT;				//random Position
		newBlockhead.dx = ((float)rand() / RAND_MAX) * 1; newBlockhead.dy = ((float)rand() / RAND_MAX) * 1;	//random speed
		newBlockhead.size = (rand() % 10) + 10;																//random size between 10 and 20
		newBlockhead.color = SDL_MapRGBA(surface->format, rand() % 255, rand() % 255, rand() % 255, 255);	//random UINT32 color
		blockhead_list[index] = newBlockhead;																//assign new BLockhead to array memory location


		printf("newNode added at index: %d, posX:%f, posY%f, dX:%f, dY%f\n", index, blockhead_list[index].x, blockhead_list[index].y, blockhead_list[index].dx, blockhead_list[index].dy);
	}
	printf("\n");
	printf("Added the Blockheads :)/n");
};
//kill some HeadNodes randomly 10% chance
void decapitateSomeHeads(struct BLOCKHEAD_NODE *blockhead_list, int mousePosX = NULL, int mousePosY = NULL)
{
	int ranKill, numHead = 0;
	if (listSize > 0)
	{
		for (int index = 0; index < listSize; index++)
		{
			++numHead;									//keep track of head count
			if (mousePosX != NULL && mousePosY != NULL)	//deleting specific nodes
			{
				if ((mousePosX >= blockhead_list[index].x) && (mousePosX <= (blockhead_list[index].x + blockhead_list[index].size)) &&
					(mousePosY >= blockhead_list[index].y) && (mousePosY <= (blockhead_list[index].y + blockhead_list[index].size)))
				{
					for (int offset = 0; offset < listSize - index - 2; offset++)
					{
						if (listSize != 1)
							blockhead_list[index + offset] = blockhead_list[index + offset + 1]; //Move Blockhead at index to end of list
					}
					--numHead;
				}
			}
			else if (mousePosX == NULL && mousePosY == NULL)								//deleting random node
			{
				if ((ranKill = rand() % 10) == 1)		//10% chance of death
				{
					printf("Node killed: %d\n", numHead);
					if (listSize != 1)
					{
						for (int offset = 0; offset < listSize - index - 2; offset++)
							blockhead_list[index + offset] = blockhead_list[index + offset + 1]; //Move Blockhead at index to end of list
					}
					--numHead;
				}
			}
		}
		printf("Heads left: %d\n", numHead);
		listSize = numHead;						//adjust size of array
		blockhead_list = (struct BLOCKHEAD_NODE*)realloc(blockhead_list, numHead * sizeof(BLOCKHEAD_NODE));
	}
	else
		printf("No heads to decapitate!\n");
};
//slow down all blockheads movement speed
void slowHeads(struct BLOCKHEAD_NODE *blockhead_list)
{
	if (listSize > 0)
	{
		for (int index = 0; index < listSize; index++)
		{
			if (blockhead_list[index].dx < 0)
				blockhead_list[index].dx += 0.01f;
			else
				blockhead_list[index].dx -= 0.01f;
			if (blockhead_list[index].dy < 0)
				blockhead_list[index].dy += 0.01f;
			else
				blockhead_list[index].dy -= 0.01f;
		}
	}
	else
		printf("No blockheads to slow down\n");
};
//speed up all blockheads movement speed
void speedHeads(struct BLOCKHEAD_NODE *blockhead_list)
{
	if (listSize > 0)
	{
		for (int index = 0; index < listSize; index++)
		{
			if ((blockhead_list[index].dx > 0) && (blockhead_list[index].dy < (float)1))
				blockhead_list[index].dx += 0.01f;
			else
				blockhead_list[index].dy -= 0.01f;
			if ((blockhead_list[index].dy > 0) && (blockhead_list[index].dy < (float)1))
				blockhead_list[index].dy += 0.01f;
			else
				blockhead_list[index].dy -= 0.01f;
		}
	}
	else
		printf("No blockheads to speed up\n");
};
//draw the BlockHeadNode
void renderBlockHead(struct BLOCKHEAD_NODE *blockhead)
{
	SDL_FreeSurface(surface);
	surface = SDL_GetWindowSurface(window);						//Get Surface

	//My pixel Variables
	pixFmt = surface->format;									//Set Color Format
	Uint8 Red, Green, Blue, Alpha;								//Get UINT8 Colors from UINT32
	SDL_GetRGBA(blockhead->color, pixFmt, &Red, &Green, &Blue, &Alpha);

	SDL_Rect  HeadRect, EyeRect0, EyeRect1, MouthRect;
	int Sizeing = blockhead->size / 5;

	printf("x:%f, y:%f\n", blockhead->x, blockhead->y);

	HeadRect.x = blockhead->x; HeadRect.y = blockhead->y;		//setposition of Head rectangle
	HeadRect.h = blockhead->size; HeadRect.w = blockhead->size;	//set dimensions
	SDL_SetRenderDrawColor(renderer, Red, Green, Blue, Alpha);	//set Rect color
	SDL_RenderFillRect(renderer, &HeadRect);					//Color blockhead rect
	SDL_RenderDrawRect(renderer, &HeadRect);

	//Eyes
	EyeRect0.x = blockhead->x + Sizeing; EyeRect0.y = blockhead->y + Sizeing;
	EyeRect0.h = Sizeing; EyeRect0.w = Sizeing;
	EyeRect1.x = blockhead->x + Sizeing * 3; EyeRect1.y = blockhead->y + Sizeing;
	EyeRect1.h = Sizeing; EyeRect1.w = Sizeing;

	//mouth
	MouthRect.x = blockhead->x + Sizeing; MouthRect.y = blockhead->y + Sizeing * 3;
	MouthRect.h = Sizeing; MouthRect.w = Sizeing * 4;

	//draw face feautures
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &EyeRect0);
	SDL_RenderDrawRect(renderer, &EyeRect0);
	SDL_RenderFillRect(renderer, &EyeRect1);
	SDL_RenderDrawRect(renderer, &EyeRect1);
	SDL_RenderFillRect(renderer, &MouthRect);
	SDL_RenderDrawRect(renderer, &MouthRect);
};
//Move the HeadNode
void moveBlockHead(struct BLOCKHEAD_NODE *blockhead)
{
	//check if going or outside of bounds of screen and invert directions
	if ((blockhead->x + blockhead->dx + blockhead->size) >= SCREEN_WIDTH)
	{
		blockhead->x = (SCREEN_WIDTH - blockhead->size);
		blockhead->dx = (-1 * blockhead->dx);
	}
	else if (blockhead->x + blockhead->dx <= 0)
	{
		blockhead->x = 0;
		blockhead->dx = (-1 * blockhead->dx);
	}
	if ((blockhead->y + blockhead->dy + blockhead->size) >= SCREEN_HEIGHT)
	{
		blockhead->y = (SCREEN_HEIGHT - blockhead->size);
		blockhead->dy = (-1 * blockhead->dy);
	}
	else if (blockhead->y + blockhead->dy <= 0)
	{
		blockhead->y = 0;
		blockhead->dy = (-1 * blockhead->dy);
	}
	else //move Blockhead cordinates
	{
		blockhead->x += blockhead->dx; blockhead->y += blockhead->dy;
	}
};
//Draw all the HeadNodes and Move them
void updateBlockHeadList(struct BLOCKHEAD_NODE *blockhead_list)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);											//clear Window

	if (listSize > 0 )
	{
		//go through all the nodes, draw and move them
		for (int index = 0; index < listSize; index++)
		{
			moveBlockHead(&blockhead_list[index]);
			//printf("Moved now Rendering blockhead: %d",index);
			renderBlockHead(&blockhead_list[index]);					//pass pointer to blockhead at index and draw it
		}
	}
	else
		printf("Null Blockheads");

	/*printf("here! 1");
	sprintf_s(stringBuff, "blocks:%d", listSize);					//convert int to string to be displayed
	SDL_FreeSurface(textSurface);									//always free befor re writing to
	printf("here! 2");
	textSurface = TTF_RenderText_Solid(font, stringBuff, fontColor);//Text for numBlockheads
	printf("here! 3");
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);	//Create texture to apply to transparent rectangle
	printf("here! 4");
	SDL_RenderCopy(renderer, texture, NULL, MessageRect);
	printf("here! 5");
	SDL_DestroyTexture(texture);									//destroy texturer after applying to free for use*/
};
//Clean up and free memory
void deAllocateMemory(struct BLOCKHEAD_NODE *blockhead_list)
{
	free(blockhead_list);				//free array holder
	//free(MessageRect);					//Free Message Rectangle
	//TTF_CloseFont(font);				//CleanUp Font
	SDL_DestroyWindow(window);			//destroy Window
	SDL_DestroyRenderer(renderer);		//destroy renderer
	SDL_FreeSurface(surface);			//Free surface
	SDL_FreeSurface(textSurface);
	printf("Freed Memory\n");
};

