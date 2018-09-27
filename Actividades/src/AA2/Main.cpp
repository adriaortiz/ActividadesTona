#include "../../dep/inc/SDL.h"					// Always needs to be included for an SDL app
#include "../../dep/inc/SDL_image.h"

#include <exception>
#include <iostream>
#include <string>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int, char*[]) 
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
		throw "No es pot inicialitzar SDL subsystems";

	// --- INIT WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr) 
		throw "No es pot inicialitzar SDL_Window";

	// --- INIT RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr) 
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	//-->SDL_Mix

	// --- SPRITES ---
		//Background
		SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };		//Carregem la textura
		if (bgTexture == nullptr) throw "Error: bgTexture init";							//Throw error en cas necesari 
		SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };									//Definim la posicio i amplada i altura 
	//-->Animated Sprite ---

	// --- TEXT ---

	// --- AUDIO ---

	// --- GAME LOOP ---
	SDL_Event event;																		//Inicialitzar els events exteriors (inputs, p.ej)
	bool isRunning = true;																	//Boolea per correr el joc 
	while (isRunning) {																		//Game LOOP
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {														//Si pulsamos una tecla 
			switch (event.type) {															//
			case SDL_QUIT:																	//Si es la tecla ESCAPE
				isRunning = false;															//
				break;
			case SDL_KEYDOWN:																//
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; 
				break;
			default:;
			}
		}

		// UPDATE

		// DRAW
		SDL_RenderClear(m_renderer);
			//Background
			SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
		SDL_RenderPresent(m_renderer);

	}																						//Sortim de IsRunning = Sortir del joc 

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);															//Destruim imatges
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);														//Destruim el render
	SDL_DestroyWindow(m_window);															//Destruim la finestra 

	// --- QUIT ---
	SDL_Quit();																				//Sortim de SDL 

	return 0;
}