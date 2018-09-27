#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <math.h>
#include <queue>
#include <map>


// Enum de lo Inputs
#pragma region InputsType
enum inputType {
	RIGHT,
	LEFT,
	EXIT,
	SPACE,
	ZERO,
	ONE,
	TWO,
	THREE,
	MAX
};
#pragma endregion


//Enum de Control de Joc
#pragma region GameState
enum gameState
{
	MENU,
	PLAY,
	SCORE,
	RANKING
};

#pragma endregion

// constantes Colores
#pragma region Colors
const USHORT PINK = 13;
const USHORT BLUE = 1;
const USHORT YELLOW = 14;
const USHORT RED = 12;
const USHORT CYAN = 11;
const USHORT GREEN = 10;
const USHORT WHITE = 15;
#pragma endregion

// constantes chars elementos
#pragma region Symbols
const char BALL = '*';
const char H_LIMIT = '_';
const char V_LIMIT = '|';
const char BLOCK = '@';
const char PADDLE = '-';
const char NULL_BLOCK = ' ';
#pragma endregion

const int X = 0;
const int Y = 1;

const int RANKING_MAX_SIZE = 21;




