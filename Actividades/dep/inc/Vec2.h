#pragma once
//#include "Utilities.h";
#include "..\inc\Utilities.h"

class Vec2
{
public:

	Vec2();
	Vec2(int _x, int _y);
	~Vec2();

private:
	int x;
	int y;

public:

	int& operator[] (int id);

	friend void operator+(Vec2 &,const Vec2 &);

	friend void operator+=(Vec2 &,const Vec2 &);

	friend bool operator==(const Vec2 &,const Vec2 &);

	friend void operator*(Vec2 &,const int &);

	friend void operator*=(Vec2 &, const Vec2 &);

	friend bool operator!=(const Vec2 &, const Vec2 &);
};

