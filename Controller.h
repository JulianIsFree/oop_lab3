#pragma once
#include <memory>
#include <vector>
#include "Ship.h"
#include "Logic.h"

class Event;

class Controller
{
public:
	virtual std::unique_ptr<Event*> onTurn();
};

class ShipController : public Controller
{
protected:
	int fieldW;
	int fieldH;
	std::vector<Ship> ships;
	virtual void generateShipPosition() { ships.clear(); };
public:
	ShipController() : fieldW(10), fieldH(10) { generateShipPosition(); };
	const std::vector<Ship>& getShips() const { return ships; };
};

class RandomShipController : public ShipController
{
protected:
	std::vector<Point> attackSequence;
	virtual void generateAttackSequence();
	virtual void generateShipPosition() override;
public:
	RandomShipController() { generateShipPosition(); generateAttackSequence(); };
	virtual std::unique_ptr<Event*> onTurn() override;
};

class ExternalShipController : public ShipController
{
protected:
	virtual void generateShipPosition() override;
public:
	ExternalShipController() { generateShipPosition(); };
	virtual std::unique_ptr<Event*> onTurn() override;
};

class OptimalShipController : public RandomShipController
{
	bool canPlase(const Ship& ship);
	bool tryPlaseHorisontalLine(Ship &ship, const int y);
	bool tryPlaseVerticalLine(Ship &ship, const int x);
	void allocateBigShips();
	void allocateLittleShips();
protected:
	virtual void generateShipPosition() override;
public:
	OptimalShipController() { generateShipPosition(); };
};
