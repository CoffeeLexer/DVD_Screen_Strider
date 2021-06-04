#define SDL_MAIN_HANDLED
#define SDL_IMAGE_HANDLED
#define FRAME_RATE 60

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_syswm.h>

int main(int argc, const char * argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    IMG_Init(IMG_INIT_PNG);
    int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
    int desktopHeight = GetSystemMetrics(SM_CYSCREEN);

    SDL_Window* window = SDL_CreateWindow("DVD Screen Strider",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        desktopWidth,
        desktopHeight,
        SDL_WINDOW_BORDERLESS);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Texture *tex = IMG_LoadTexture(renderer, "DVD.png");
    SDL_Rect rect = {0, 0, 601, 271};

    SDL_SetTextureColorMod(tex, rand() % 100 + 150, rand() % 100 + 150, rand() % 100 + 150);

    SDL_RenderCopy(renderer, tex, NULL, &rect);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;

    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    SDL_RenderPresent(renderer);

    int xSpeed = 3;
    int ySpeed = 3;

    bool active = false;
    SDL_Event event;
    int ticks = SDL_GetTicks();
    while (!active) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                active = true;
            }
        }
        if(SDL_GetTicks() > ticks + 1000 / FRAME_RATE)
		{
            ticks += 1000 / FRAME_RATE;
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, tex, NULL, &rect);
            SDL_RenderPresent(renderer);

            if(rect.x + xSpeed < 0 || rect.x + rect.w + xSpeed > desktopWidth)
            {
                SDL_SetTextureColorMod(tex, rand() % 100 + 50, rand() % 100 + 50, rand() % 100 + 50);
                xSpeed *= -1;
            }
            if(rect.y + ySpeed < 0 || rect.y + rect.h + ySpeed > desktopHeight)
            {
                SDL_SetTextureColorMod(tex, rand() % 100 + 50, rand() % 100 + 50, rand() % 100 + 50);
                ySpeed *= -1;
            }

            rect.x += xSpeed;
            rect.y += ySpeed;
        }
        else
        {
            SDL_Delay(14);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}