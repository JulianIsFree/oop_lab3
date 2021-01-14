#pragma once
#include "Exception.h"
#include <string>

class LogicException : public Exception
{
protected:
	std::string getCoords(int x, int y) { return "(" + std::to_string(x) + "," + std::to_string(y) + ")"; };
public:
	LogicException(const std::string &why) : Exception("Game logic exception: " + why) {};
};

class CellIsAlreadyAttacked : public LogicException
{
public:
	CellIsAlreadyAttacked(int x, int y) : LogicException(getCoords(x,y) + " cell is already attacked or attached to orion of dead ship") {};
};

class BadCoords : public LogicException
{
public:
	BadCoords(int x, int y) : LogicException(getCoords(x, y) + " are bad coords to attack") {};
};