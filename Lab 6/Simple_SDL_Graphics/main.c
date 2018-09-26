//Name: Thomas Gilman
//Modification of: Paul Yost's code
//Class: ETEC 2110
//Section: 51
//Assignment: 6
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

    //Screen dimension constants
    int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
    //Screen Background color
    int Red = 255, Green = 255, Blue = 255;
    //While loop handler
    int waiting = 1;



int main(int argc, char *argv[])
{
    SDL_Window* window = NULL; //The window we'll be rendering to
    SDL_Surface* screenSurface = NULL; //The surface contained by the window
    SDL_Event myEvent; //Event that should be polled for
    //Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf( "SDL not initialized. SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
        //Get window surface
        screenSurface = SDL_GetWindowSurface( window );
        //Fill the surface white
        SDL_FillRect( screenSurface, NULL,
        SDL_MapRGB( screenSurface->format, Red, Green, Blue ) );
        //Update the surface
        SDL_UpdateWindowSurface( window );
        }
    }
    //random Seed
    srand(time(0));
    while(waiting)
    {
        SDL_PollEvent(&myEvent);
        switch(myEvent.type)
        {
            case SDL_KEYDOWN:
                switch( myEvent.key.keysym.sym )
                {
                    //Randomize screen colors and update screen
                    case SDLK_r:
                        Red = rand() % 256;
                        Green = rand() % 256;
                        Blue = rand() % 256;
                        SDL_FillRect( screenSurface, NULL,
                                     SDL_MapRGB(screenSurface->format, Red, Green, Blue));
                        SDL_UpdateWindowSurface( window );
                        break;

                    //escape Window
                    case SDLK_ESCAPE:
                        SDL_DestroyWindow( window );
                        SDL_Quit();
                        waiting = 0;
                        break;

                    default:
                        break;
                }
                break;

            //escape Window
            case SDL_QUIT:
                SDL_DestroyWindow( window ); //Destroy window
                SDL_Quit();                 //Quit SDL subsystems
                waiting = 0;
                break;

            default:
                break;
        }
    }
}
