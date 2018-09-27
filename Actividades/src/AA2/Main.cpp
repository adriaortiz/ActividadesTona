#include "../../dep/inc/SDL.h"					// Always needs to be included for an SDL app
#include "../../dep/inc/SDL_image.h"
#include "../../dep/inc/SDL_ttf.h"

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
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_ttf";							//Throw de la font de lletra 
	//-->SDL_Mix

	// --- SPRITES ---
		//Background
		SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };		//Carregem la textura
		if (bgTexture == nullptr) throw "Error: bgTexture init";							//Throw error en cas necesari 
		SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };									//Definim la posicio i amplada i altura 

		//Ratolí
		SDL_Texture* playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
		if (playerTexture == nullptr) throw "No s' han pogut crear les textures";
		SDL_Rect playerRect{0,0,350,189};
	//-->Animated Sprite ---
		SDL_Rect playerTarget{ 0,0,100,100};
	// --- TEXT ---
		//No val la pena fer servir aixo en temps real (carregar les imatges no, pero mostrarles o no, es pot fer)
		TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",70) };					//Obrir la font amb el tamany
		if (font == nullptr) throw "No es pot inicialitzar TTF_Font";
		SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font,"My first SDL game", SDL_Color{255,150,0,255}) };		//Variable per la font a carregar, el text i el color 
		if (tmpSurf == nullptr) throw "Unable to create the SDL teach";
		SDL_Texture *textTexture{SDL_CreateTextureFromSurface(m_renderer, tmpSurf)};
		SDL_Rect textRect{100,50,tmpSurf->w, tmpSurf->h };									//
		SDL_FreeSurface(tmpSurf);															//Amb la surface alliberada, podem aprofitar la mateixa Surface per fer un altre text i no fer mes variables
		TTF_CloseFont(font);

		//Hover
		tmpSurf = { TTF_RenderText_Blended(font, "My first SDL game", SDL_Color{100,201,170,255 })};
		SDL_Texture *textTexture2{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

	// --- AUDIO ---

	// --- GAME LOOP ---
	SDL_Event event;																		//Inicialitzar els events exteriors (inputs, p.ej)
	bool isRunning = true;																	//Boolea per correr el joc 
	while (isRunning) {																		//Game LOOP
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {														//Si pulsamos una tecla. El while es más preciso que el if. SOlo sirven para recojer, no para loopear
			switch (event.type) {															//Segun el tipo del input, recorremos un switch (como SDL_KEYDOWN o SDL_MOUSEBUTTONDOWN)
			case SDL_QUIT:																	//Si es la tecla ESCAPE
				isRunning = false;															//Salimos del juego
				break;
			case SDL_KEYDOWN:																//
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; 
				break;
			//event.key.keysym --> Teclat: SDLK_LEFT, SDLK_SPACE
			//event.button.button --> Ratolí: SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT
			case SDL_MOUSEMOTION:
				//playerRect.x = event.motion.x - playerRect.w/2;								//El kintoun sempre seguira la flecha i estara centrat
				//playerRect.y = event.motion.y - playerRect.h/2;
				playerTarget.x = event.motion.x - playerRect.w / 2;
				playerTarget.y = event.motion.y - playerRect.h / 2;
				break;
			default:;
			}
		}

		// UPDATE			//Aqui es donde se aplica toda la logica
		playerRect.x += (playerTarget.x - playerRect.x) / 10;
		playerRect.y += (playerTarget.y - playerRect.y) / 10;
		if (true) {
			//Collisons 
		}
		// DRAW
		SDL_RenderClear(m_renderer);
			//Background
			SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
			//Player Cursor 
			SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);
			//Text
			SDL_RenderCopy(m_renderer,textTexture,nullptr,&textRect);
			//Hover
			SDL_RenderCopy(m_renderer, textTexture2, nullptr, &textRect);

		SDL_RenderPresent(m_renderer);

	}																						//Sortim de IsRunning = Sortir del joc 

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);															//Destruim imatges
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textTexture2);
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(m_renderer);														//Destruim el render
	SDL_DestroyWindow(m_window);															//Destruim la finestra 

	// --- QUIT ---
	SDL_Quit();																				//Sortim de SDL 

	return 0;
}