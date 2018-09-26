//Thomas Gilman
//Systems Programming
//ETEC 2110
//51
//Lab 9
//part 2 SNAKE GAME
#include "stdafx.h"
#include "Snake.h"

Snake::Snake(SDL_Window *window, SDL_Renderer *renderer, int gameWidth, int gameHeight)
{
	SCREEN_WIDTH = gameWidth; SCREEN_HEIGHT = gameHeight;
	//Setup Image texture
	const char* PATH = "C:\\Users\\Thoma\\OneDrive\\Documents\\programs\\SystemsProg\\Lab 9\\SNAKE_Game\\resources\\creepy.jpg";
	if ((snakeSurface = IMG_Load(PATH)) == NULL)
		printf("Could not loag image: %s\n", IMG_GetError());
	snakeTexture = SDL_CreateTextureFromSurface(renderer, snakeSurface);

	//Free Surface and set it for color format
	SDL_FreeSurface(snakeSurface);
	snakeSurface = SDL_GetWindowSurface(window);

	for (int index = 0; index < bodySize; index++)
	{
		BODY newBody;
		if (index == 0)	//Head of body
		{
			newBody.x = (rand() % SCREEN_WIDTH - newBody.size) + newBody.size;
			newBody.y = (rand() % SCREEN_HEIGHT - newBody.size)+ newBody.size;
			newBody.color = SDL_MapRGBA(snakeSurface->format, rand() % 255, rand() % 255, rand() % 255, 255);	//random color
		}
		else			//Body part
		{
			newBody.x = SnakeList[index - 1].x - newBody.size;
			newBody.y = SnakeList[index - 1].y;
			newBody.color = SnakeList[index - 1].color;
		}
		printf("SnakeBody%d, posX:%f, posY:%f\n", index, newBody.x, newBody.y);
		SnakeList.push_back(newBody);
	}
};
bool Snake::moveSnake(Apple *appleToEat, SDL_Renderer *renderer, SDL_Keycode sysEvent)
{
	if (sysEvent != NULL)
	{
		lastKeyPressed = sysEvent;
		printf("keyPressed %d\n", lastKeyPressed);
	}
	for (iter = SnakeList.begin(); iter < SnakeList.end(); iter++)
	{
		switch (lastKeyPressed)
		{
		case SDLK_UP:
		case SDLK_w:
			if (iter == SnakeList.begin())	//move head up
			{
				iter->y -= iter->speed;
				iter->direction2 = 4;
			}
			break;

		case SDLK_DOWN:
		case SDLK_s:
			if (iter == SnakeList.begin())	//move head down
			{
				iter->y += iter->speed;
				iter->direction2 = 2;
			}
			break;

		case SDLK_LEFT:
		case SDLK_a:
			if (iter == SnakeList.begin())	//move head left
			{
				iter->x -= iter->speed;
				iter->direction = 3;
			}
			break;

		case SDLK_RIGHT:
		case SDLK_d:
			if (iter == SnakeList.begin())	//move head right
			{
				iter->x += iter->speed;
				iter->direction = 1;
			}
			break;

		default:
			break;
		}
		if (iter == SnakeList.begin())	//move head left
		{
			if ((iter->y < 0) || ((iter->y + iter->size) > SCREEN_HEIGHT) ||	//going outside of bounds
				(iter->x < 0) || ((iter->x + iter->size) > SCREEN_WIDTH))
				return false;
			/*for (int index = 1; index < bodySize; index++)						//Check if head running into body
			{
				//if origin x of head or right most point of origin rect intersects with body x
				//and origin y of head or bottom most point of origin rect intersect with body y return false
				if (( ((iter->x >= SnakeList[index].x) || ((iter->x + iter->size) >= SnakeList[index].x)) &&	//originX or furthest right greater or eqaul origin of body part
					( (iter->x <= (SnakeList[index].x + SnakeList[index].size)) ||								//originX or furthest right less or equal to furthest right of body part
					( (iter->x + iter->size) <= (SnakeList[index].x + SnakeList[index].size) )) &&	
					( ((iter->y >= SnakeList[index].y) || ((iter->y + iter->size)  >= SnakeList[index].y) )) &&	//originY or furthest down greater or equal than origin of body part
					( (iter->y <= (SnakeList[index].y + SnakeList[index].size)) ||								//originY or furthest down less or equal to furthest down of body part
					( (iter->y + iter->size) <= (SnakeList[index].y + SnakeList[index].size))) ))
					return false;
			}*/
			//check if eating apple
			if ( ((iter->y >= appleToEat->getYPos()) || ((iter->y + iter->size) >= appleToEat->getYPos())) &&	//origin or furthest down greater or equal to apple posY
				( (iter->x >= appleToEat->getXPos()) || ((iter->x + iter->size) >= appleToEat->getXPos())) &&	//origin or furthest right greater or equal to apple posX
				( (iter->y <= (appleToEat->getYPos() + appleToEat->getSize())) ||								//origin or furthest down less or equal to apples furthest down
				( (iter->y + iter->size) <= (appleToEat->getYPos() + appleToEat->getSize()))) &&
				( (iter->x <= (appleToEat->getXPos() + appleToEat->getSize())) ||								//origin or furthest right less or equal to apples furthest right
				( (iter->x + iter->size) <= (appleToEat->getXPos() + appleToEat->getSize()) )))
			{
				growSnake();
				appleToEat->newApple(renderer);
				printf("I ate an apple!, snake Size: %d", bodySize);
				iter = SnakeList.begin();
			}
		}
		else if(iter != SnakeList.begin())	//body
		{

			if ((iter->x + iter->size) > (iter - 1)->x) (iter)->direction = 1;
			if (iter->x < ((iter - 1)->x + (iter - 1)->size)) (iter)->direction = 3;
			if (iter->y > ((iter - 1)->y + (iter - 1)->size)) (iter)->direction2 = 2;
			if ((iter->y + iter->size) < (iter - 1)->y) (iter)->direction2 = 4;

			if (iter->direction == 1) iter->x -= iter->speed;		//right
			if (iter->direction == 3) iter->x += iter->speed;		//left
			if (iter->direction2 == 2) iter->y -= iter->speed;		//down
			if (iter->direction2 == 4) iter->y += iter->speed;		//up
		}
	}
	return true;
};
int Snake::getSize()
{
	return bodySize;
}
void Snake::renderSnake(SDL_Renderer *renderer)
{
	//My pixel Variables
	pixFmt = snakeSurface->format;								//Set Color Format
	Uint8 Red, Green, Blue, Alpha;								//Get UINT8 Colors from UINT32

	for (iter = SnakeList.begin(); iter < SnakeList.end(); iter++)
	{
		SDL_GetRGBA(iter->color, pixFmt, &Red, &Green, &Blue, &Alpha); //Get RGBA

		SDL_Rect bodyRect;

		bodyRect.x = iter->x; bodyRect.y = iter->y;					//setposition of rectangle
		bodyRect.h = iter->size; bodyRect.w = iter->size;			//set dimension
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);			//set Rect color
		SDL_RenderFillRect(renderer, &bodyRect);					//Color Rect
		SDL_RenderDrawRect(renderer, &bodyRect);

		//SDL_RenderCopy(renderer, snakeTexture, NULL, &bodyRect);	//display image on rectangle
	}
};
//insert new body part at end of list, Snake will extend as it moves
void Snake::growSnake()
{
	BODY newBody;
	newBody.x = SnakeList.front().x + SnakeList.front().size;
	newBody.y = SnakeList.front().y;
	newBody.color = SnakeList.front().color;
	SnakeList.push_back(newBody);
	for (iter = SnakeList.begin() + 1; iter < SnakeList.end(); iter++)
	{
		if(iter->x > (iter-1)->x) iter->x += iter->size;
		if(iter->x < (iter - 1)->x) iter->x -= iter->size;
	}
		
	bodySize++;
};
void Snake::printSnake_Data()
{
	for (iter = SnakeList.begin(); iter < SnakeList.end(); iter++)
		cout << "SnakeBody positions are x: " << iter->x << " y: " << iter->y << endl;
};
Snake::~Snake()
{
	SnakeList.clear();					//free vector memory
	SDL_DestroyTexture(snakeTexture);	//destroy texture
	SDL_FreeSurface(snakeSurface);		//free surface
	cout << "Freed Snake memory!, Snake Destroyed" << endl;
};
