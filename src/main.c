#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// gcc src/*.c -o prog -lmingw32 -lSDL2main -lSDL2

const int WINDOW_WIDTH = 768, WINDOW_HEIGHT = 512;

void drawState(SDL_Renderer *renderer, int *array, int red, int green){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	for(int i = 0; i < 768; i++){
		if(i == red)
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		else if(i == green)
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		else
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_RenderDrawLine(renderer, i, WINDOW_HEIGHT-1, i, array[i]);
	}
	SDL_RenderPresent(renderer);
}

void merge(int *array, int *left, int l_size, int *right, int r_size){
	int i = 0, j = 0, k = 0;
	while(i < l_size || j < r_size){
		array[k++] = i > l_size ? right[j++] : j > r_size ? left[i++] : left[i] < right[j] ? left[i++] : right[j++];
	}
}

void mergeSort(){

}

int main(int argc, char **argv){
	//Init SDL, a Window and a Renderer
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Sort Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Fill the array
	srand(time(NULL));
	int *array = malloc(sizeof(int) * 768);
	for(int i = 0; i < 768; i++){
		array[i] = rand() % WINDOW_HEIGHT;
	}
	
	int comparisons = 0;
	for(int i = 0; i < 768; i++){
		for(int j = 0; j < 768; j++){
			if(array[i] < array[j]){
				const int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			drawState(renderer, array, j, i);
			comparisons++;
		}
		SDL_Delay(50);
	}
	printf("Comparisons: %d\n", comparisons);

	//Main Loop
	bool quit = false;
	while(!quit){
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0){
			switch(event.type){
				case SDL_QUIT:
					quit = true;
					break;
				default:
					break;
			}
		}
	}

	//Destroy the Renderer, Window and close SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return(0);
}