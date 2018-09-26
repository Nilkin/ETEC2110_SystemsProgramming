//Thomas Gilman
//ETEC2110
//51
//Lab 8 program 1
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#pragma once

//SDL Variables
SDL_Window *window;					//My window
SDL_Surface *surface, *textSurface;	//My surface
SDL_Renderer *renderer;				//my Renderer
SDL_PixelFormat *pixFmt;			//my Pixel Format specifier
SDL_Texture *texture;				//my Texturer
SDL_Event sysEvent;					//myEvent Handler
TTF_Font *font;
SDL_Color color = { 255, 0, 0 , 255};	//font color

SDL_Rect *MessageRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

struct BLOCKHEAD_NODE
{
	float x, y;		// position
	float dx, dy;	// movement component
	long color;		//UINT32 Color pattern
	int size;		//size between 10-20
	struct BLOCKHEAD_NODE * next;
};
//Creat a BlockHeadList
struct BLOCKHEAD_NODE* initBlockHeadList(int listSize = 30)
{
	MessageRect->x = 0; MessageRect->y = 0; MessageRect->w = 200; MessageRect->h = 50;

	printf("Created BlockHead Nodes: %d\n", listSize);
	//seed Random and get Surface
	srand(time(0)); surface = SDL_GetWindowSurface(window);

	//create firstBlockHead
	struct BLOCKHEAD_NODE* BlockHead = (struct BLOCKHEAD_NODE*)malloc(sizeof(struct BLOCKHEAD_NODE));
	BlockHead->x = rand() % SCREEN_WIDTH; BlockHead->y = rand() % SCREEN_HEIGHT;						//random Position
	BlockHead->dx = ((float)rand() / RAND_MAX) * 1; BlockHead->dy = ((float)rand() / RAND_MAX) * 1;		//random speed
	BlockHead->size = (rand() % 10) + 10;																//random size between 10 and 20
	BlockHead->color = SDL_MapRGBA(surface->format, rand() % 255, rand() % 255, rand() % 255, 255);		//random color
	--listSize;

	struct BLOCKHEAD_NODE *nodePtr = BlockHead;

	while(listSize--)
	{
		printf("BlockHead%d, posX:%f, posY:%f, dX:%f, dY%f\n", listSize - 30, BlockHead->x, BlockHead->y, BlockHead->dx, BlockHead->dy);

		struct BLOCKHEAD_NODE* newBlockHead = (struct BLOCKHEAD_NODE*)malloc(sizeof(struct BLOCKHEAD_NODE));//make next BLOCKHEAD
		newBlockHead->x = rand() % SCREEN_WIDTH; newBlockHead->y = rand() % SCREEN_HEIGHT;					//random Position
		newBlockHead->dx = ((float)rand() / RAND_MAX) * 1; newBlockHead->dy = ((float)rand() / RAND_MAX) * 1;	//random speed
		newBlockHead->size = (rand() % 10) + 10;															//random size between 10 and 20
		newBlockHead->color = SDL_MapRGBA(surface->format, rand() % 255, rand() % 255, rand() % 255, 255);	//random color

		BlockHead->next = newBlockHead;
		BlockHead = newBlockHead;
	}
	BlockHead->next = NULL; //last BlockHeads next is NULL

	//Return ptr to first BLOCKHEAD
	return nodePtr;
}
void getBlockHeads(struct BLOCKHEAD_NODE *BlockHeadList)
{
	if (BlockHeadList == NULL)
		printf("Passed empty LinkedList, No BLOCKHEADS");
	
	int numHeads = 0;
	struct BLOCKHEAD_NODE *HeadPtr = BlockHeadList;
	while (HeadPtr != NULL && BlockHeadList != NULL)
	{
		printf("Blockhead%d position is x:%f, y:%f, Speed is dx:%f, dy:%f\n", numHeads++, HeadPtr->x, HeadPtr->y, HeadPtr->dx, HeadPtr->dy);
		HeadPtr = HeadPtr->next;
	}
	printf("\n");
}
//Add some more Nodes to the end of the list
void addMoreHeads(struct BLOCKHEAD_NODE* BlockHeadList, int numOfHeads = 10, int mousePosX = NULL, int mousePosY = NULL)
{
	printf("addingSomeHeads\n");
	struct BLOCKHEAD_NODE *headPtr = BlockHeadList;
	surface = SDL_GetWindowSurface(window);

	//move to end of LinkedList
	while (headPtr->next != NULL && headPtr !=NULL)	
		headPtr = headPtr->next;
	//add new BLOCKHEADS
	while (numOfHeads--)
	{
		struct BLOCKHEAD_NODE *newBlockHead = (struct BLOCKHEAD_NODE*)malloc(sizeof(struct BLOCKHEAD_NODE));	//create another Node
		if (mousePosX != NULL && mousePosY != NULL)	
		{
			newBlockHead->x = mousePosX; newBlockHead->y = mousePosY;											//Adding Node at specific location
		}
		else
			newBlockHead->x = rand() % SCREEN_WIDTH; newBlockHead->y = rand() % SCREEN_HEIGHT;					//random Position
		newBlockHead->dx = ((float)rand() / RAND_MAX) *1 ; newBlockHead->dy = ((float)rand() / RAND_MAX) * 1;	//random speed
		newBlockHead->size = (rand() % 10) + 10;																//random size between 10 and 20
		newBlockHead->color = SDL_MapRGBA(surface->format, rand() % 255, rand() % 255, rand() % 255, 255);		//random color
		
		printf("newNode added, posX:%f, posY%f, dX:%f, dY%f\n", newBlockHead->x, newBlockHead->y, newBlockHead->dx, newBlockHead->dy);				
		//Point and move to next Node
		if (headPtr == NULL)
		{
			headPtr = newBlockHead;
		}
		else
		{
			headPtr->next = newBlockHead;
			headPtr = headPtr->next;
		}
	}
	printf("\n");
	headPtr->next = NULL;
}
//kill some HeadNodes randomly 10% chance
struct BLOCKHEAD_NODE* decapitateSomeHeads(struct BLOCKHEAD_NODE *blockhead_list, int mousePosX = NULL, int mousePosY = NULL)
{
	struct BLOCKHEAD_NODE *curNode = blockhead_list, *prevHead = NULL, *firstNode = blockhead_list;
	int ranKill, numHead = 0;
	while (curNode != NULL)
	{
		if (mousePosX != NULL && mousePosY != NULL)	//deleting specific nodes
		{
			if ((mousePosX >= curNode->x) && (mousePosX <= (curNode->x + curNode->size)) && (mousePosY >= curNode->y) && (mousePosY <= (curNode->y + curNode->size)))
			{
				if (numHead == 0) // first node
				{
					firstNode = firstNode->next;	//first node is moved
					free(curNode);					//free prev headnode
					curNode = firstNode;			//point to cur headnode now
				}
				else
				{
					prevHead->next = curNode->next;	//make prev next point to cur next
					free(curNode);					//free cur node
					curNode = prevHead->next;		//move cur node to next node
				}
				--numHead;
			}
			else
			{
				prevHead = curNode;			//move prev forward
				curNode = curNode->next;	//move cur Node forward
			}
		}
		else	//deleting random node
		{
			if ((ranKill = rand() % 10) == 1) //10% chance of death
			{
				printf("Node killed: %d\n", numHead);
				if (numHead == 0) // first node
				{
					firstNode = firstNode->next;	//first node is moved
					free(curNode);					//free prev headnode
					curNode = firstNode;			//point to cur headnode now
				}
				else
				{
					prevHead->next = curNode->next;	//make prev next point to cur next
					free(curNode);					//free cur node
					curNode = prevHead->next;		//move cur node to next node
				}
				--numHead;
			}
			else
			{
				prevHead = curNode;			//move prev forward
				curNode = curNode->next;	//move cur Node forward
			}
		}
		++numHead;
	}
	printf("Heads left: %d\n", numHead);

	return firstNode;
}
//slow down all blockheads movement speed
void slowHeads(struct BLOCKHEAD_NODE *blockhead_list)
{
	if (blockhead_list == NULL)
		printf("No blockheads to slow down");
	struct BLOCKHEAD_NODE *headPtr = blockhead_list;
	float decX = 0.01, decY = 0.01;
	while (headPtr != NULL)
	{
		if (headPtr->dx < 0)
			headPtr->dx += decX;
		else
			headPtr->dy -= decX;
		if (headPtr->dy < 0)
			headPtr->dy += decY;
		else
			headPtr->dy -= decY;
		headPtr = headPtr->next;
	} 
}
//speed up all blockheads movement speed
void speedHeads(struct BLOCKHEAD_NODE *blockhead_list)
{
	if (blockhead_list == NULL)
		printf("No blockheads to speed up");
	struct BLOCKHEAD_NODE *headPtr = blockhead_list;
	float decX = 0.01, decY = 0.01;
	while(headPtr != NULL)
	{
		if ((headPtr->dx > 0) && (headPtr->dy < (float)1))
			headPtr->dx += decX;
		else
			headPtr->dy -= decX;
		if ((headPtr->dy > 0) && (headPtr->dy < (float)1))
			headPtr->dy += decY;
		else
			headPtr->dy -= decY;
		headPtr = headPtr->next;
	}
}
//draw the BlockHeadNode
void renderBlockHead(struct BLOCKHEAD_NODE *blockhead)
{
	//My pixel Variables
	pixFmt = surface->format;
	Uint8 Red, Green, Blue, Alpha;
	SDL_GetRGBA(blockhead->color, pixFmt, &Red, &Green, &Blue, &Alpha);
	
	SDL_Rect  HeadRect, EyeRect0, EyeRect1, MouthRect;
	int Sizeing = blockhead->size / 5;

	HeadRect.x = blockhead->x; HeadRect.y = blockhead->y;		//setposition of Head rectangle
	HeadRect.h = blockhead->size; HeadRect.w = blockhead->size;	//set dimensions
	SDL_SetRenderDrawColor(renderer, Red, Green, Blue, Alpha);	//set Rect color
	SDL_RenderFillRect(renderer, &HeadRect);					//Color blockhead rect
	SDL_RenderDrawRect(renderer, &HeadRect);

	//Eyes
	EyeRect0.x = blockhead->x + Sizeing; EyeRect0.y = blockhead->y + Sizeing;
	EyeRect0.h = Sizeing; EyeRect0.w = Sizeing;
	EyeRect1.x = blockhead->x + Sizeing*3; EyeRect1.y = blockhead->y + Sizeing;
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
}
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
}
//Draw all the HeadNodes
void renderBlockHeadList(struct BLOCKHEAD_NODE *blockhead_list)
{	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);										//clear Window

	int numBlockHeads = 0;
	char stringBuff[200];
	
	while (blockhead_list != NULL)//go through all the nodes and draw them should go through atleast once
	{
		numBlockHeads++;
		renderBlockHead(blockhead_list);
		blockhead_list = blockhead_list->next;
	}
	sprintf_s(stringBuff, "blocks:%d", numBlockHeads);				//convert int to string to be displayed
	SDL_FreeSurface(textSurface);									//always free befor re writing to
	textSurface = TTF_RenderText_Solid(font, stringBuff, color);	//Text for numBlockheads
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);	//Create texture to apply to transparent rectangle
	SDL_RenderCopy(renderer, texture, NULL, MessageRect);
	SDL_DestroyTexture(texture);									//destroy texturer after applying to free for use
}
//Move all the HeadNodes
void moveBlockHeadList(struct BLOCKHEAD_NODE *blockhead_list)
{
	struct BLOCKHEAD_NODE *headPtr = blockhead_list;
	while (headPtr != NULL)//go through all the nodes and move them, should go through atleast once
	{
		moveBlockHead(headPtr);
		headPtr = headPtr->next;
	}
}
void updateBlockHeadList(struct BLOCKHEAD_NODE *blockhead_list)
{
	if (blockhead_list != NULL)
	{
		moveBlockHeadList(blockhead_list);
		renderBlockHeadList(blockhead_list);
	}
	else
		printf("Null Blockheads");
}
//Clean up and free memory
void deAllocateMemory(struct BLOCKHEAD_NODE *blockhead_list)
{
	struct BLOCKHEAD_NODE *nextHeadPtr;
	while (blockhead_list != NULL)		//clean up and free memory
	{
		nextHeadPtr = blockhead_list->next;
		free(blockhead_list);
		blockhead_list = nextHeadPtr;
	}
	free(MessageRect);					//Free last HeadNode
	TTF_CloseFont(font);				//CleanUp Font
	SDL_DestroyWindow(window);			//destroy Window
	SDL_DestroyRenderer(renderer);		//destroy renderer
	SDL_FreeSurface(surface);			//Free surface
	SDL_FreeSurface(textSurface);
	printf("Freed Memory\n");
}