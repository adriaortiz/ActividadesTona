#include "../../dep/inc/SDL.h"					// Always needs to be included for an SDL app
#include "../../dep/inc/SDL_image.h"
#include "../../dep/inc/SDL_ttf.h"
#include "../../dep/inc/SDL_mixer.h"

#include <exception>
#include <iostream>
#include <string>

#include <time.h>								//Para calcular delta time

//En casa: 10.0.16299.0
//En la uni: 10.0.17134.0

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const int FPS = 60;
const int DELAY_TIME = 1000.0f/FPS;

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
	const Uint8 mixFlags(MIX_INIT_MP3 | MIX_INIT_OGG);
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error";

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);										//SDL Mixer esta inicialitzat


	// --- TIME ---
	clock_t lastTime = clock();
	float timeDown = 60.;									//Ideal para realizar una cuenta atras 
	float deltaTime = 0;

	Uint8 frameStart, frameTime = 1;





	// --- SPRITES ---
		//Background Main Menu
		SDL_Texture* bgTextureMainMenu{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };		//Carregem la textura
		if (bgTextureMainMenu == nullptr) throw "Error: bgTexture init";							//Throw error en cas necesari 
		SDL_Rect bgRectMainMenu{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };									//Definim la posicio i amplada i altura 

		//Background Play
		SDL_Texture* bgTexturePlay{ IMG_LoadTexture(m_renderer, "../../res/img/bgCastle.jpg") };		
		if (bgTexturePlay == nullptr) throw "Error: bgTexture init";
		SDL_Rect bgRectPlay{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };								

		//Ratolí
		SDL_Texture* playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
		if (playerTexture == nullptr) throw "No s' han pogut crear les textures";
		SDL_Rect playerRect{0,0,350,189};
		SDL_Rect playerTarget{ 0,0,100,100 };
	//-->Animated Sprite ---
		SDL_Texture *runnerText{ IMG_LoadTexture(m_renderer, "../../res/img/sp01.png") };
		SDL_Rect runnerRect, runnerPosition;
		int textWidth, textHeight, frameWidth, frameHeight;
		SDL_QueryTexture(runnerText, NULL, NULL, &textWidth,&textHeight);
		frameWidth = textWidth / 6;								//Tallem la llargada del sprite en 6 parts
		frameHeight = textHeight / 1;							//Tallem la altura del sprite en 1 part 
		runnerPosition.x = runnerPosition.y = 0;				
		runnerRect.x = runnerRect.y = 0;
		runnerPosition.h = runnerRect.h = frameHeight;			
		runnerPosition.w = runnerRect.w = frameWidth;


	// --- TEXT ---
		//No val la pena fer servir aixo en temps real (carregar les imatges no, pero mostrarles o no, es pot fer)

		//Main Menu
			//Play Button
			TTF_Font *fontSaiyan70{ TTF_OpenFont("../../res/ttf/saiyan.ttf",70) };					//Obrir la font amb el tamany
			if (fontSaiyan70 == nullptr) throw "No es pot inicialitzar TTF_Font";
			SDL_Surface *tmpSurf{ TTF_RenderText_Blended(fontSaiyan70,"Play", SDL_Color{255,150,0,255}) };		//Variable per la font a carregar, el text i el color 
			if (tmpSurf == nullptr) throw "Unable to create the SDL teach";
			SDL_Texture *textTexturePlay{SDL_CreateTextureFromSurface(m_renderer, tmpSurf)};
			SDL_Rect textRectPlay{100,50,tmpSurf->w, tmpSurf->h };		
		
			//Hover Play 
			tmpSurf = { TTF_RenderText_Blended(fontSaiyan70, "Play", SDL_Color{ 100,201,170,255 }) };
			SDL_Texture *textTexturePlayHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect textRectPlayHover{ 100,50,tmpSurf->w, tmpSurf->h };
		

			//Sound off
			tmpSurf = { TTF_RenderText_Blended(fontSaiyan70,"Sound off", SDL_Color{ 255,150,0,255 }) };
			SDL_Texture *textTextureSoundOff{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect textRectSoundOff{ 100,150,tmpSurf->w, tmpSurf->h };

			//Sound off Hover
			tmpSurf = { TTF_RenderText_Blended(fontSaiyan70,"Sound off", SDL_Color{ 100,201,170,255 }) };
			SDL_Texture *textTextureSoundOffHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect textRectSoundOffHover{ 100,150,tmpSurf->w, tmpSurf->h };

			//Sound On
			tmpSurf = { TTF_RenderText_Blended(fontSaiyan70,"Sound on", SDL_Color{ 255,150,0,255 }) };
			SDL_Texture *textTextureSoundOn{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect textRectSoundOn{ 100,150,tmpSurf->w, tmpSurf->h };

			//Sound On Hover
			tmpSurf = { TTF_RenderText_Blended(fontSaiyan70,"Sound On", SDL_Color{ 100,201,170,255 }) };
			SDL_Texture *textTextureSoundOnHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect textRectSoundOnHover{ 100,150,tmpSurf->w, tmpSurf->h };

			//Exit
			tmpSurf = { TTF_RenderText_Blended(fontSaiyan70,"Exit", SDL_Color{ 255,150,0,255 }) };
			SDL_Texture *textTextureExit{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect textRectExit{ 100,250,tmpSurf->w, tmpSurf->h };									//

			//Exit Hover
			tmpSurf = { TTF_RenderText_Blended(fontSaiyan70,"Exit", SDL_Color{ 100,201,170,255 }) };
			SDL_Texture *textTextureExitHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect textRectExitHover{ 100,250,tmpSurf->w, tmpSurf->h };			

		//Play
			TTF_Font *fontSaiyan40{ TTF_OpenFont("../../res/ttf/saiyan.ttf",40) };					//Obrir la font amb el tamany
			if (fontSaiyan40 == nullptr) throw "No es pot inicialitzar TTF_Font";
			tmpSurf = { TTF_RenderText_Blended(fontSaiyan40,"PlayerOne", SDL_Color{0,0,0,255}) };			//Variable per la font a carregar, el text i el color 
			if (tmpSurf == nullptr) throw "Unable to create the SDL teach";
			SDL_Texture *textTexturePlayer1{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect textRectPlayer1{ 20,20,tmpSurf->w, tmpSurf->h };

			tmpSurf = { TTF_RenderText_Blended(fontSaiyan40,"PlayerTwo", SDL_Color{ 0,0,0,255 }) };
			SDL_Texture *textTexturePlayer2{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect textRectPlayer2{ 20,70,tmpSurf->w, tmpSurf->h };

		SDL_FreeSurface(tmpSurf);																	//Superficie alliberada 
		TTF_CloseFont(fontSaiyan70);

		

	// --- AUDIO ---
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			//Frequencia: Sortida de la frequencia
			//Format: Format de sortida
			//Canals: 2 per estereo, 1 per a mono
			//Chunksize: bytes utlitzats per mostra de sortida 
			throw "Unable to init SDL_Mixer";
		}
		Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
		if (!soundtrack) throw "Unable to load Mix_Music soundtrack";
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
		Mix_PlayMusic(soundtrack, -1);

		Mix_Music *backgroundMusic = Mix_LoadMUS("../../res/au/mainTheme.mp3");
		//En cas d' efectes d' audio puntuals, Mix_Chunk *jumpEffect = Mix_LoadWAV("../../res/au/mainTheme.wav")

	// --- VARIABLES ---
		// --- Buttons ---
		bool MouseInPlayButton = false;
		bool MouseInSoundButton = false;
		bool MouseInExitButton = false;
		bool MouseButtonDown = false;

		bool MusicOn = true;
		int Scene = 0;						//0: Menu	1: Play 
	
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

		frameStart = SDL_GetTicks();
		
		//Movimiento del ratón
		playerRect.x += (playerTarget.x - playerRect.x) / 10;
		playerRect.y += (playerTarget.y - playerRect.y) / 10;


		frameTime++;
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		std::cout << timeDown << std::endl;			//Tiempo actual;
		

		
		
		if (FPS / frameTime <= 9) {
			frameTime = 0;
			runnerRect.x += frameWidth;
			if (runnerRect.x >= textWidth) {
				runnerRect.x = 0;
			}
		}


		if (event.motion.x > textRectPlay.x&& event.motion.x < textRectPlay.x + textRectPlay.w &&
			event.motion.y > textRectPlay.y&& event.motion.y < textRectPlay.y + textRectPlay.h) {
			MouseInPlayButton = true;
			if (MouseButtonDown) {
				//Cambi d' escena
				Scene = 1;
			}
		}
		else MouseInPlayButton = false;

		if (event.motion.x > textRectSoundOff.x&& event.motion.x < textRectSoundOff.x + textRectSoundOff.w &&
			event.motion.y > textRectSoundOff.y&& event.motion.y < textRectSoundOff.y + textRectSoundOff.h) {
			if (MusicOn) {
				MouseInSoundButton = true;
				if (MouseButtonDown) {
					Mix_CloseAudio();
					MusicOn = false;
				}
			}
			else {
				MouseInSoundButton = true;
				if (MouseButtonDown) {
					Mix_PlayMusic(backgroundMusic, -1);
					MusicOn = true;
				}
			}
			
			
		}
		else MouseInSoundButton = false;

		if (event.motion.x > textRectExit.x&& event.motion.x < textRectExit.x + textRectExit.w &&
			event.motion.y > textRectExit.y&& event.motion.y < textRectExit.y + textRectExit.h) {
			MouseInExitButton = true;
			if (MouseButtonDown) {
				isRunning = false;
			}
		}
		else MouseInExitButton = false;

		

			
	
	
		// DRAW
		SDL_RenderClear(m_renderer);
		if (Scene == 0) {
			//Background
			SDL_RenderCopy(m_renderer, bgTextureMainMenu, nullptr, &bgRectMainMenu);
			//Player Cursor 
			SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);
			if (!MouseInPlayButton) {		//Text Play	
				SDL_RenderCopy(m_renderer, textTexturePlay, nullptr, &textRectPlay);
			}
			else {							//Text Play Hover
				SDL_RenderCopy(m_renderer, textTexturePlayHover, nullptr, &textRectPlayHover);
			}

			if (MusicOn) {
				if (!MouseInSoundButton) {	//Text Sound off
					SDL_RenderCopy(m_renderer, textTextureSoundOff, nullptr, &textRectSoundOff);
				}
				else {							//Text Sound off Hover
					SDL_RenderCopy(m_renderer, textTextureSoundOffHover, nullptr, &textRectSoundOffHover);
				}
			}
			else
				if (!MouseInSoundButton) {	//Text Sound off
					SDL_RenderCopy(m_renderer, textTextureSoundOn, nullptr, &textRectSoundOn);
				}
				else {							//Text Sound off Hover
					SDL_RenderCopy(m_renderer, textTextureSoundOnHover, nullptr, &textRectSoundOnHover);
				}

			if (!MouseInExitButton) {		//Text Exit
				SDL_RenderCopy(m_renderer, textTextureExit, nullptr, &textRectExit);
			}
			else {							//Text Exit Hover
				SDL_RenderCopy(m_renderer, textTextureExitHover, nullptr, &textRectExitHover);
			}

			SDL_RenderCopy(m_renderer, runnerText, &runnerRect, &runnerPosition);
		}
		else if (Scene == 1) {
			//Background
			SDL_RenderCopy(m_renderer, bgTexturePlay, nullptr, &bgRectPlay);

			//Player1 Texto
			SDL_RenderCopy(m_renderer, textTexturePlayer1, nullptr, &textRectPlayer1);

			//Player2 Texto
			SDL_RenderCopy(m_renderer, textTexturePlayer2, nullptr, &textRectPlayer2);
		}
				

				
				
			

		SDL_RenderPresent(m_renderer);

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}

	}																						//Sortim de IsRunning = Sortir del joc 

	// --- DESTROY ---
	SDL_DestroyTexture(bgTextureMainMenu);															//Destruim imatges
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(textTexturePlay);
	SDL_DestroyTexture(textTexturePlayHover);
	SDL_DestroyTexture(textTextureSoundOff);
	SDL_DestroyTexture(textTextureSoundOffHover);
	SDL_DestroyTexture(textTextureExit);
	SDL_DestroyTexture(textTextureExitHover);

	SDL_DestroyTexture(bgTexturePlay);
	Mix_FreeMusic(backgroundMusic);
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(m_renderer);														//Destruim el render
	SDL_DestroyWindow(m_window);															//Destruim la finestra 

	// --- QUIT ---
	SDL_Quit();																				//Sortim de SDL 

	return 0;
}
