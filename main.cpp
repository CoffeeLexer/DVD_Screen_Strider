#define SDL_MAIN_HANDLED
#define SDL_IMAGE_HANDLED
#define FRAME_RATE 60

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, const char * argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Screen Strider", 0, 0, 600, 271, SDL_WINDOW_BORDERLESS);
    SDL_Event event;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    IMG_Init(IMG_INIT_PNG);
    bool active = true;
    unsigned int ticks = SDL_GetTicks();
    int x = 0;
    int y = 0;
    int dirX = 3;
    int dirY = 3;
    SDL_SetWindowOpacity(window, 0.5);
    SDL_Rect rect;
    SDL_GetDisplayBounds(0, &rect);
    printf("%i %i %i %i\n", rect.x, rect.y, rect.w, rect.h);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);
    SDL_Texture *tex = IMG_LoadTexture(renderer, "DVD.png");
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Surface *s;
    s = SDL_GetWindowSurface(window);
    SDL_memset(s->pixels, 0, s->h * s->w * 4);
    while(active)
    {
        while(SDL_PollEvent(&event) > 0)
		{
			switch(event.type)
			{
				case SDL_QUIT:
					active = false;
					break;
			}
		}
        if(SDL_GetTicks() > ticks + 1000 / FRAME_RATE)
        {
            ticks += 1000 / FRAME_RATE;
            SDL_SetWindowPosition(window, x, y);
            x+= dirX;
            y+= dirY;
            if(x + dirX < 0 | x + dirX + 600 > rect.w)
            {
                dirX *= -1;
            }
            if(y + dirY < 0 | y + dirY + 271 > rect.h)
            {
                dirY *= -1;
            }
        }
        else 
        {
            SDL_Delay(1);
        }
    }
    SDL_Quit();
}