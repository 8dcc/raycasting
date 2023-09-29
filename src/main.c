
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include "include/main.h"
#include "include/bresenham.h"
#include "include/raycast.h"
#include "include/rotation.h"

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
        arr[15 * ARR_W + x] = 255;

    for (int y = 15; y < 35; y++)
        arr[y * ARR_W + 20] = 255;

    /* Light source */
    const vec2_t center = {
        .x = ARR_W / 2,
        .y = ARR_H / 2,
    };

    /* Cast rays from center to all sides (360) */
    vec2_t cast;
    for (int y = 0; y < ARR_H; y++) {
        vec2_t tmp0 = { 0, y };
        raycast_line(center, tmp0, &cast);
        bresenham_line(center, cast);

        vec2_t tmp1 = { ARR_W - 1, y };
        raycast_line(center, tmp1, &cast);
        bresenham_line(center, cast);
    }

    for (int x = 0; x < ARR_W; x++) {
        vec2_t tmp0 = { x, 0 };
        raycast_line(center, tmp0, &cast);
        bresenham_line(center, cast);

        vec2_t tmp1 = { x, ARR_H - 1 };
        raycast_line(center, tmp1, &cast);
        bresenham_line(center, cast);
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
