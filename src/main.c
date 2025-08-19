#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BAR_MAX_COUNT 400
#define BAR_WIDTH 2

// Global array
int arr[BAR_MAX_COUNT];
int n = BAR_MAX_COUNT;  // Number of elements
int bar_width = BAR_WIDTH;
int sorting_in_progress = 0;
int paused = 0;
int highlight1 = -1, highlight2 = -1;

SDL_Renderer* renderer = NULL;
int max_val = 0;

// Function pointer for current sort
void (*sort_func)(int*, int, void (*)(int, int)) = NULL;

void recalc_max(void) {
    max_val = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }
}

void init_array(void) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000 + 1;
    }
    recalc_max();
}

// Render bars
void render_bars(SDL_Renderer *renderer, int *arr, int n) { 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < n; i++) {
        int bar_height = (int)((double)arr[i] / max_val * (WINDOW_HEIGHT - 50));
        SDL_Rect bar = {
            .x = i * bar_width,
            .y = WINDOW_HEIGHT - bar_height,
            .w = bar_width,
            .h = bar_height
        };

        if (i == highlight1 || i == highlight2) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Highlight
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderFillRect(renderer, &bar);
    }
    SDL_RenderPresent(renderer);
}

void swap_callback(int i, int j) {
    highlight1 = i;
    highlight2 = j;
    render_bars(renderer, arr, n);
    highlight1 = highlight2 = -1;
    SDL_Delay(1);
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Sorting Visualiser",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,
                                       SDL_WINDOW_SHOWN);
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    srand((unsigned int)time(NULL));
    init_array();

    SDL_Event e;
    int running = 1;
    while (running) {
      while (SDL_PollEvent(&e)) {
	if (e.type == SDL_QUIT) {
	  running = 0;
	  printf("test");
	} else if (e.type == SDL_KEYDOWN) {
	  switch (e.key.keysym.sym) {
          case SDLK_q:
            running = 0;
            break;
          case SDLK_r:
            init_array();
            break;

          case SDLK_p:
            paused = !paused;
            break;

          case SDLK_1:
            sorting_in_progress = 1;
            sort_func = bubble_sort;
            break;

          case SDLK_2:
            sorting_in_progress = 1;
            sort_func = insertion_sort;
            break;

          case SDLK_3:
            sorting_in_progress = 1;
            sort_func = selection_sort;
            break;

          case SDLK_4:
            sorting_in_progress = 1;
            sort_func = quick_sort;
            break;

          case SDLK_5:
            sorting_in_progress = 1;
            sort_func = merge_sort;
            break;
	    
          case SDLK_6:
            sorting_in_progress = 1;
            sort_func = heap_sort;
            break;
	    
          case SDLK_7:
            sorting_in_progress = 1;
            sort_func = shell_sort;
            break;
	    
          case SDLK_8:
            sorting_in_progress = 1;
            sort_func = radix_sort;
            break;
	    
          case SDLK_9:
            sorting_in_progress = 1;
            sort_func = bucket_sort;
            break;
	    
          case SDLK_0:
            sorting_in_progress = 1;
            sort_func = counting_sort;
            break;
	    
	  default: break;
	  }
	}
      }

      if (sorting_in_progress && sort_func) {
	sort_func(arr, n, swap_callback);
	sorting_in_progress = 0;
	recalc_max();
      }
      
      render_bars(renderer, arr, n);
      SDL_Delay(0);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
