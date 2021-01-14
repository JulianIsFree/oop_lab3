#pragma once
#include <memory>

class Controller;
class Player;
class Viewer;

class Session
{
protected:
	std::shared_ptr<Player*> p1, p2;
	int rounds;
public:
	Session(Player *p1, Player *p2, int rounds);
	void run();
};
