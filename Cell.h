#pragma once
class Cell
{
public:
	int x;
	int y;
	bool isAttacked;
	Cell(int x, int y) : x(x), y(y), isAttacked(false) {};
};
