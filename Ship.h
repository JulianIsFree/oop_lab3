#pragma once
#include <string>

#include "Logic.h"

class Ship : public Rectangle, public Entity
{
protected:
	std::string name;
	int hp;
public:
	Ship(int width, int heigth, int hp=1, const std::string& name="Ship") : Rectangle(width, heigth), Entity(true), hp(hp), name(name) {};
	Ship(Point p1, Point p2, int hp = 1, const std::string& name = "Ship") : Rectangle(p1, p2), Entity(true), hp(hp), name(name) {};
	Ship(Point p1, int width, int heigth, int hp = 1, const std::string& name = "Ship") : Rectangle(p1, width, heigth), Entity(true), hp(hp), name(name) {};

	Rectangle getOrion() const;
	bool isCollision(const Ship& other) const;
	bool isCollision(Point p) const { return Rectangle::isCollision(p); };

	virtual void onDamage() override;

	operator std::string() const;
};

class BattleShip : public Ship
{
public:
	BattleShip() : Ship(1, 4, 4, "BattleShip") {};
	BattleShip(Point p1) : Ship(p1, 4, 1, 4, "BattleShip") {};
};

class Cruiser : public Ship
{
public:
	Cruiser() : Ship(1, 3, 3, "Cruiser") {};
	Cruiser(Point p1) : Ship(p1, 3, 1, 3, "Cruiser") {};
};

class Destroyer : public Ship
{
public:
	Destroyer() : Ship(1, 2, 2, "Destroyer") {};
	Destroyer(Point p1) : Ship(p1, 2, 1, 2, "Destroyer") {};
};

class Boat : public Ship
{
public:
	Boat() : Ship(1, 1, 1, "Boat") {};
	Boat(Point p1) : Ship(p1, 1, 1, 1, "Boat") {};
};
