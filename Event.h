#pragma once
#include <vector>
#include "Logic.h"

class Player;

class Event
{
public:
	virtual void run(Player& p, Player& t) const {};
};

class AttackEvent : public Event
{
	Point target;
public:
	AttackEvent(Point target) : target(target) {};
	virtual void run(Player& p, Player& t) const override;
};

class SurrenderEvent : public Event
{
	std::string why;
public:
	SurrenderEvent(const std::string& why) : why(why) {};
	virtual void run(Player& p, Player& t) const override;
};
