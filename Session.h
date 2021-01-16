#pragma once
#include <memory>

class Controller;
class Player;
class Viewer;

class Session
{
protected:
	int rounds;
public:
	Session(int rounds);
	virtual void run() {};
};
