#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

void rotate_y(float vertecies[], double a)
{
    int i = 0;
    for (i = 0; i < 24; i+=3) {
        float tmp = vertecies[i]*cos(a) - vertecies[i+2]*sin(a);
        vertecies[i+2] = vertecies[i+2]*cos(a) + vertecies[i]*sin(a);
        vertecies[i] = tmp;
    }
}

void rotate_x(float vertecies[], double a)
{
    int i = 0;
    for (i = 0; i < 24; i+=3) {
        float tmp = vertecies[i+1]*cos(a) + vertecies[i+2]*sin(a);
        vertecies[i+2] = vertecies[i+2]*cos(a) - vertecies[i+1]*sin(a);
        vertecies[i+1] = tmp;
    }
}

void rotate_z(float vertecies[], double a)
{
    int i = 0;
    for (i = 0; i < 24; i+=3) {
        float tmp = vertecies[i]*cos(a) + vertecies[i+1]*sin(a);
        vertecies[i+1] = vertecies[i+1]*cos(a) - vertecies[i]*sin(a);
        vertecies[i] = tmp;
    }
}

void main()
{
    float vertecies[24] = { -2, -2, -2, 2, -2, -2, -2, 2, -2, -2, -2, 2, 2, 2, -2, 2, -2, 2, -2, 2, 2, 2, 2, 2 };
    const short int edges[24] = { 0, 1, 0, 2, 0, 3, 1, 4, 1, 5, 2, 4, 2, 6, 3, 6, 3, 5, 5, 7, 6, 7, 7, 4 };
    const short int fov = -20;
    const short int screen_color[3] = { 0x00, 0x00, 0x00 };
    const short int height = 300;
    const short int width = 300;
    const short int scale = 30;
    const double pi = 3.141592;
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else {
        window = SDL_CreateWindow( "Cube", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0 );
        if( window == NULL ) {
            printf( "Windwo could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else {
            SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_Event e;
            bool quit = false;
            while(!quit)
            {
                while( SDL_PollEvent( &e ) ){
                    if( e.type == SDL_QUIT ) quit = true;
                }
                SDL_Delay(2);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                rotate_y(vertecies, 0.001*pi);
                rotate_z(vertecies, 0.001*pi);
                int i = 0;
                for (i = 0; i < 24; i+=2) {
                    int tmp = 0;
                    int x1 = vertecies[edges[i]*3]*fov/(vertecies[edges[i]*3+2] + fov)*scale+width/2;
                    int y1 = vertecies[edges[i]*3+1]*fov/(vertecies[edges[i]*3+2] + fov)*scale+width/2;
                    int x2 = vertecies[edges[i+1]*3]*fov/(vertecies[edges[i+1]*3+2] + fov)*scale+width/2;
                    int y2 = vertecies[edges[i+1]*3+1]*fov/(vertecies[edges[i+1]*3+2] + fov)*scale+width/2;
                    SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
                    SDL_RenderDrawLine( renderer, x1, y1, x2, y2);
                }
                SDL_RenderPresent(renderer);
            }
        }
    }
}
