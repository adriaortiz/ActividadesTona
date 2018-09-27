#pragma once
//#include "Vec2.h"
#include "..\inc\Vec2.h"



class Board
{
	//Constructors
public:
	Board();
	~Board();

	//Variables
private:
	const std::string pathConfig = "config.txt";
	int rows;
	int columns;
	int blockRows;

	int currentBlocks;
	int minScore;
	int maxScore;
	std::queue<int> *scoreQueue;
	int score;
	int lives;

#pragma region Elements
public:
	class Cell
	{
	public:
		//Constuctors
		Cell(): cellChar(' '),color(0) {};
		Cell(char _cellChar, USHORT _color) : cellChar(_cellChar), color(_color) {};
		~Cell();
		char cellChar;
		USHORT color;
	}  **board;
		
	class Ball
	{
	public:
		Ball() :position(Vec2()) {};
		Ball(int _x, int _y) : position(Vec2(_x, _y)), speed(Vec2(0,0)) {};
		~Ball();
		Vec2 position;
		Vec2 speed;
		bool ballMovement(Vec2 boardDimentions,int blockRows, Vec2 paddlePos, Board &);

		void setSpeed(Vec2 newSpeed)
		{
			speed = newSpeed;
		}

	}*ball;

	class Paddle
	{
	public:
		Paddle() :position(Vec2()) {};
		Paddle(int x, int y) : position(Vec2(x - 3, y/2)),large(3) {};
		~Paddle();

		Vec2 position;
		int large;

		//FUNCTIONS
		void paddleMovement(inputType currentInput, Ball *ball, int columns);

	}*paddle;

#pragma endregion

	//Functions
public:
	void readBoardSize();
	void initBoard();
	void initScore(const int&);
	void drawBoard();
	void drawInfo();
	void refreshBoard();
	void clearElement();
	void refreshElement();
	bool boardEmpty();

	Vec2 getDimensions();
	int getRows();
	int getBlockRows();
	int getColumns();
	int getScore();
	int getLives();
	void minLives(int value);
	int blocksXcent();
};

