
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include "include/main.h"
#include "include/bresenham.h"
#include "include/raycast.h"
#include "include/rotation.h"

#define FPS   60
#define SCALE 2

uint8_t arr[ARR_H * ARR_W] = { 0 };

static void die(char* s) {
    fprintf(stderr, "%s\n", s);
    SDL_Quit();
    exit(1);
}

static inline void draw_raycast(vec2_t start, vec2_t end) {
    vec2_t cast = raycast_line(start, end);
    bresenham_line(start, cast);
}

/* Ran each frame before rendering arr */
static void draw_loop(void) {
    static float ang = 1.f;

    /* Light source */
    static const vec2_t eyes = {
        .x = ARR_W / 2,
        .y = ARR_H / 2,
    };

    /* Center of FOV */
    static const vec2_t view = {
        .x = ARR_W - 5,
        .y = ARR_H / 2,
    };

    /* Clear */
    for (int y = 0; y < ARR_H; y++)
        for (int x = 0; x < ARR_W; x++)
            set_val(y, x, 0);

    /* NOTE: Test walls */
    for (int x = 50; x < 90; x++)
        set_val(35, x, 255);
    for (int y = 35; y < 55; y++)
        set_val(y, 50, 255);

    ang = (ang > 360.f) ? 0.f : ang + 1;

#if 0
    draw_angle(ang, eyes, view);
#else
    vec2_t tmp = rotate_rel(DEG2RAD(ang), eyes, view);
    draw_raycast(eyes, tmp);

    /* TODO: Use raycasting when drawing angle. You can't just use draw_raycast
     * because it would leave gaps. */
    /* draw_angle(FOV, eyes, tmp); */
#endif

#if 0
    vec2_t fov_start = rotate_rel(DEG2RAD(FOV / 2), eyes, view);
    vec2_t fov_end   = rotate_rel(DEG2RAD(-(FOV / 2)), eyes, view);
    draw_raycast(eyes, view);
    draw_raycast(eyes, fov_start);
    draw_raycast(eyes, fov_end);

    /* Cast rays from eyes to all sides (360) */
    for (int y = 0; y < ARR_H; y++) {
        draw_raycast(eyes, (vec2_t){ 0, y });
        draw_raycast(eyes, (vec2_t){ ARR_W - 1, y });
    }

    for (int x = 0; x < ARR_W; x++) {
        draw_raycast(eyes, (vec2_t){ x, 0 });
        draw_raycast(eyes, (vec2_t){ x, ARR_H - 1 });
    }
#endif
}

int main() {
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

        /* Make changes to global array */
        draw_loop();

        /* Iterate global array */
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
