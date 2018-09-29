#include "../../dep/inc/SDL.h"					// Always needs to be included for an SDL app
#include "../../dep/inc/SDL_image.h"
#include "../../dep/inc/SDL_ttf.h"
#include "../../dep/inc/SDL_mixer.h"

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

	// --- AUDIO RENDER ---
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		throw "No es pot inicialitzar SDL audio";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_ttf";							//Throw de la font de lletra pero... bastant inutil aqui 

	//-->SDL_Mix
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);										//SDL Mixer esta inicialitzat


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
		//Play
		TTF_Font *fontPlay{ TTF_OpenFont("../../res/ttf/saiyan.ttf",70) };					//Obrir la font amb el tamany
		if (fontPlay == nullptr) throw "No es pot inicialitzar TTF_Font";
		SDL_Surface *tmpSurfPlay{ TTF_RenderText_Blended(fontPlay,"Play", SDL_Color{255,150,0,255}) };		//Variable per la font a carregar, el text i el color 
		if (tmpSurfPlay == nullptr) throw "Unable to create the SDL teach";
		SDL_Texture *textTexturePlay{SDL_CreateTextureFromSurface(m_renderer, tmpSurfPlay)};
		SDL_Rect textRectPlay{100,50,tmpSurfPlay->w, tmpSurfPlay->h };									//
		SDL_FreeSurface(tmpSurfPlay);															//Amb la surface alliberada, podem aprofitar la mateixa Surface per fer un altre text i no fer mes variables
		TTF_CloseFont(fontPlay);

		//Hover Play 
		TTF_Font *fontPlayHover{ TTF_OpenFont("../../res/ttf/saiyan.ttf",70) };					//Obrir la font amb el tamany
		if (fontPlayHover == nullptr) throw "No es pot inicialitzar TTF_Font";
		SDL_Surface *tmpSurfPlayHover = { TTF_RenderText_Blended(fontPlayHover, "Play", SDL_Color{ 100,201,170,255 }) };
		SDL_Texture *textTexturePlayHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfPlayHover) };
		SDL_Rect textRectPlayHover{ 100,50,tmpSurfPlayHover->w, tmpSurfPlayHover->h };
		SDL_FreeSurface(tmpSurfPlayHover);
		TTF_CloseFont(fontPlayHover);

		//Sound off
		TTF_Font *fontSoundOff{ TTF_OpenFont("../../res/ttf/saiyan.ttf",70) };					//Obrir la font amb el tamany
		if (fontSoundOff == nullptr) throw "No es pot inicialitzar TTF_Font";
		SDL_Surface *tmpSurfSoundOff{ TTF_RenderText_Blended(fontSoundOff,"Sound off", SDL_Color{ 255,150,0,255 }) };
		if (tmpSurfSoundOff == nullptr) throw "Unable to create the SDL teach";
		SDL_Texture *textTextureSoundOff{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfSoundOff) };
		SDL_Rect textRectSoundOff{ 100,150,tmpSurfSoundOff->w, tmpSurfSoundOff->h };									//
		SDL_FreeSurface(tmpSurfSoundOff);															//Superficie alliberada 
		TTF_CloseFont(fontSoundOff);

		//Sound off Hover
		TTF_Font *fontSoundOffHover{ TTF_OpenFont("../../res/ttf/saiyan.ttf",70) };					//Obrir la font amb el tamany
		if (fontSoundOffHover == nullptr) throw "No es pot inicialitzar TTF_Font";
		SDL_Surface *tmpSurfSoundOffHover{ TTF_RenderText_Blended(fontSoundOffHover,"Sound off", SDL_Color{ 100,201,170,255 }) };
		if (tmpSurfSoundOffHover == nullptr) throw "Unable to create the SDL teach";
		SDL_Texture *textTextureSoundOffHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfSoundOffHover) };
		SDL_Rect textRectSoundOffHover{ 100,150,tmpSurfSoundOffHover->w, tmpSurfSoundOffHover->h };									//
		SDL_FreeSurface(tmpSurfSoundOffHover);															//Superficie alliberada 
		TTF_CloseFont(fontSoundOffHover);

		//Exit
		TTF_Font *fontExit{ TTF_OpenFont("../../res/ttf/saiyan.ttf",70) };					//Obrir la font amb el tamany
		if (fontExit == nullptr) throw "No es pot inicialitzar TTF_Font";
		SDL_Surface *tmpSurfExit{ TTF_RenderText_Blended(fontExit,"Exit", SDL_Color{ 255,150,0,255 }) };
		if (tmpSurfExit == nullptr) throw "Unable to create the SDL teach";
		SDL_Texture *textTextureExit{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfExit) };
		SDL_Rect textRectExit{ 100,250,tmpSurfExit->w, tmpSurfExit->h };									//
		SDL_FreeSurface(tmpSurfExit);															//Superficie alliberada 
		TTF_CloseFont(fontExit);

		//Exit Hover
		TTF_Font *fontExitHover{ TTF_OpenFont("../../res/ttf/saiyan.ttf",70) };						//Obrir la font amb el tamany
		if (fontExitHover == nullptr) throw "No es pot inicialitzar TTF_Font";
		SDL_Surface *tmpSurfExitHover{ TTF_RenderText_Blended(fontExitHover,"Exit", SDL_Color{ 100,201,170,255 }) };
		if (tmpSurfExitHover == nullptr) throw "Unable to create the SDL teach";
		SDL_Texture *textTextureExitHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfExitHover) };
		SDL_Rect textRectExitHover{ 100,250,tmpSurfExitHover->w, tmpSurfExitHover->h };				//
		SDL_FreeSurface(tmpSurfExitHover);															//Superficie alliberada 
		TTF_CloseFont(fontExitHover);

		

	// --- AUDIO ---
		Mix_Music *backgroundMusic = Mix_LoadMUS("../../res/au/mainTheme.mp3");
		//En cas d' efectes d' audio puntuals, Mix_Chunk *jumpEffect = Mix_LoadWAV("../../res/au/mainTheme.wav")

	// --- VARIABLES ---
		// --- Buttons ---
		bool MouseInPlayButton = false;
		bool MouseInSoundOffButton = false;
		bool MouseInExitButton = false;
		bool MouseButtonDown = false;

		// --- Audio ---
		
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
				if (event.motion.x > textRectPlay.x&& event.motion.x < textRectPlay.x + textRectPlay.w &&
					event.motion.y > textRectPlay.y&& event.motion.y < textRectPlay.y + textRectPlay.h) {
					//Hay colision con el boton Play
					MouseInPlayButton = true;
				}
				else MouseInPlayButton = false;
				if (event.motion.x > textRectSoundOff.x&& event.motion.x < textRectSoundOff.x + textRectSoundOff.w &&
					event.motion.y > textRectSoundOff.y&& event.motion.y < textRectSoundOff.y + textRectSoundOff.h) {
					MouseInSoundOffButton = true;
				}
				else MouseInSoundOffButton = false;
				if (event.motion.x > textRectExit.x&& event.motion.x < textRectExit.x + textRectExit.w &&
					event.motion.y > textRectExit.y&& event.motion.y < textRectExit.y + textRectExit.h) {
					MouseInExitButton = true;
				}
				else MouseInExitButton = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				MouseButtonDown = true;
				break;
			case SDL_MOUSEBUTTONUP:
				MouseButtonDown = false;
				break;
			default:;
			}
		}

		// UPDATE			//Aqui es donde se aplica toda la logica
		playerRect.x += (playerTarget.x - playerRect.x) / 10;
		playerRect.y += (playerTarget.y - playerRect.y) / 10;
		//Collisons with buttons
		if (MouseInPlayButton) {
			//Hover Button
			if (MouseButtonDown) {
				//ButtonClicked
				backgroundMusicBool = true;
			}
		}
		else {
			//Unhover button
		}
		if (MouseInSoundOffButton) {
			//Hover Button
			if (MouseButtonDown) {
				//ButtonClicked


			}
		}
		else {

		}
		if (MouseInExitButton) {
			//Hover Button
			if (MouseButtonDown) {
				//ButtonClicked
				isRunning = false;
			}
		}
		else {

		}
	
	
		// DRAW
		SDL_RenderClear(m_renderer);
			//Background
			SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
			//Player Cursor 
			SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);
			if (!MouseInPlayButton) {		//Text Play	
				SDL_RenderCopy(m_renderer, textTexturePlay, nullptr, &textRectPlay);
			}
			else {							//Text Play Hover
				SDL_RenderCopy(m_renderer, textTexturePlayHover, nullptr, &textRectPlayHover);
			}

			if (!MouseInSoundOffButton) {	//Text Sound off
				SDL_RenderCopy(m_renderer, textTextureSoundOff, nullptr, &textRectSoundOff);
			}
			else {							//Text Sound off Hover
				SDL_RenderCopy(m_renderer, textTextureSoundOffHover, nullptr, &textRectSoundOffHover);
			}

			if (!MouseInExitButton) {		//Text Exit
				SDL_RenderCopy(m_renderer, textTextureExit, nullptr, &textRectExit);
			}
			else {							//Text Exit Hover
				SDL_RenderCopy(m_renderer, textTextureExitHover, nullptr, &textRectExitHover);
			}
				

				
				
			

		SDL_RenderPresent(m_renderer);

	}																						//Sortim de IsRunning = Sortir del joc 

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);															//Destruim imatges
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(textTexturePlay);
	SDL_DestroyTexture(textTexturePlayHover);
	SDL_DestroyTexture(textTextureSoundOff);
	SDL_DestroyTexture(textTextureSoundOffHover);
	SDL_DestroyTexture(textTextureExit);
	SDL_DestroyTexture(textTextureExitHover);
	Mix_FreeMusic(backgroundMusic);
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(m_renderer);														//Destruim el render
	SDL_DestroyWindow(m_window);															//Destruim la finestra 

	// --- QUIT ---
	SDL_Quit();																				//Sortim de SDL 

	return 0;
}