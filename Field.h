#pragma once

#include <vector>
#include "Cell.h"

class Ship;
class ShipPlayer;

class ShipField
{
private:
	int width;
	int heigth;
	std::vector<Cell> map;
	std::vector<Ship> ships;
	ShipPlayer& player;

	void initMap();
public:
	ShipField(ShipPlayer& player);
	ShipField(const std::vector<Ship>& ships, ShipPlayer& player) : width(10), heigth(10), ships(ships), player(player) { initMap(); };
	bool onAttack(int x, int y);
	void onShipDefeat(Ship& ship);
	bool anyShipsAlive();
};
