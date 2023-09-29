
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include "include/main.h"
#include "include/bresenham.h"
#include "include/raycast.h"

#define FPS   30
#define SCALE 2

uint8_t arr[ARR_H * ARR_W] = { 0 };

static void die(char* s) {
    fprintf(stderr, "%s\n", s);
    SDL_Quit();
    exit(1);
}

int main() {
    /* NOTE: Test walls */
    for (int x = 20; x < 60; x++)
        arr[16 * ARR_W + x] = 255;

    const int center_y = ARR_H / 2;
    const int center_x = ARR_W / 2;

    /* Cast rays from center to all sides (360) */
    int cast_x, cast_y;
    for (int y = 0; y < ARR_H; y++) {
        raycast_line(center_x, center_y, 0, y, &cast_x, &cast_y);
        bresenham_line(center_x, center_y, cast_x, cast_y);

        raycast_line(center_x, center_y, ARR_W - 1, y, &cast_x, &cast_y);
        bresenham_line(center_x, center_y, cast_x, cast_y);
    }

    for (int x = 0; x < ARR_W; x++) {
        raycast_line(center_x, center_y, x, 0, &cast_x, &cast_y);
        bresenham_line(center_x, center_y, cast_x, cast_y);

        raycast_line(center_x, center_y, x, ARR_H - 1, &cast_x, &cast_y);
        bresenham_line(center_x, center_y, cast_x, cast_y);
    }

    /*------------------------------------------------------------------------*/

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        die("Unable to start SDL");

    SDL_Window* sdl_window =
      SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, ARR_W * SCALE, ARR_H * SCALE, 0);

    if (!sdl_window)
        die("Error creating a window");

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* sdl_renderer =
      SDL_CreateRenderer(sdl_window, -1, render_flags);
    if (!sdl_renderer) {
        SDL_DestroyWindow(sdl_window);
        die("Error creating a renderer");
    }

    puts("Press <Esc> or <q> to exit...");

    /* Clear screen */
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl_renderer);

    /* For key events */
    SDL_Event sdl_event;

    bool sdl_loop = true;
    while (sdl_loop) {
        while (SDL_PollEvent(&sdl_event)) {
            /* Check event type */
            switch (sdl_event.type) {
                case SDL_QUIT:
                    sdl_loop = false;
                    break;
                case SDL_KEYDOWN:
                    /* Check the pressed key */
                    switch (sdl_event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                        case SDL_SCANCODE_Q:
                            sdl_loop = false;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        /* Iterate line array */
        for (int y = 0; y < ARR_H; y++) {
            for (int x = 0; x < ARR_W; x++) {
                const uint8_t val = arr[y * ARR_W + x];
                SDL_SetRenderDrawColor(sdl_renderer, val, val, val, 255);

                /* Draw SCALE*SCALE rectangle */
                SDL_Rect rect = {
                    .x = x * SCALE,
                    .y = y * SCALE,
                    .w = SCALE,
                    .h = SCALE,
                };

                SDL_RenderFillRect(sdl_renderer, &rect);
            }
        }

        /* Send to renderer */
        SDL_RenderPresent(sdl_renderer);

        SDL_Delay(1000 / FPS);
    }

    return 0;
}
