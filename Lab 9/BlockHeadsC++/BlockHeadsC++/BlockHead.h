//Thomas Gilman
//ETEC2110
//51
//Lab 9 program 1
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

//SCREEN Dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#pragma once
class BlockHead
{
public:
	BlockHead(SDL_Window *window, SDL_Renderer *renderer);
	void moveBlockHeads();
	void renderBlockHeads(SDL_Renderer *renderer);
	void addBlockHeads(int numOfHeads = 10, int mousePosX = NULL, int mousePosY = NULL);
	void deleteBlockHeads(int mousePosX = NULL, int mousePosY = NULL);
	void updateBlockHeads(SDL_Renderer *renderer);
	void speedUpHeads();
	void slowDownHeads();
	void printBlockHead_Data();
	~BlockHead();
private:
	int listSize = 30;
	char stringBuff[200];
	struct BLOCKHEAD
	{
		float x, y;		// position
		float dx, dy;	// movement component
		long color;		//UINT32 Color pattern
		int size;		//size between 10-20
	};
	std::vector<BLOCKHEAD> blockHeadList;	//dynamic array for Blockhead struct
	std::vector<BLOCKHEAD>::iterator iter;	//my Vector iterator
	SDL_Surface *textSurface, *surface;		//surface for Blockhead text
	SDL_Surface *image;						//my image surface
	SDL_Texture *BlockHeadTexture, *texture;//Texture for blockhead faces
	SDL_Rect *MessageRect = new SDL_Rect;	//Rectangle for displaying number of blockheads
	SDL_Color fontColor = { 255, 0, 0 };	//font color
	SDL_PixelFormat *pixFmt;				//my Pixel Format specifier
	TTF_Font *font;							//my font
};
