#include "Field.h"
#include "Player.h"
#include "Ship.h"
#include "Cell.h"
#include "LogicException.h"
#include "Controller.h"
#include "Logic.h"

void ShipField::initMap()
{
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < heigth; ++j)
			map.push_back(Cell(i, j));
}

ShipField::ShipField(ShipPlayer &player) : width(10), heigth(10), player(player)
{
	RandomShipController c;
	ships = c.getShips();
}

bool ShipField::onAttack(int x, int y)
{
	if (x >= width || x < 0 || y >= heigth || y < 0)
		throw BadCoords(x, y);

	if (map[x*width + y].isAttacked)
		throw CellIsAlreadyAttacked(x, y);
	
	bool anyShipDamaged = false;
	for (auto &ship : ships)
	{
		if (ship.isCollision(Point(x, y)))
		{
			ship.onDamage();
			// assumes that we couldn't attack dead ship
			if (!ship.alive())
				onShipDefeat(ship);
			anyShipDamaged = true;
		}
	}

	return anyShipDamaged;
}

void ShipField::onShipDefeat(Ship & ship)
{
	Rectangle oreon = ship.getOrion();
	Point p1 = oreon.getP1();
	Point p2 = oreon.getP2();

	for (int i = p1.x; i <= p2.x; ++i)
	{
		for (int j = p1.y; j <= p2.y; ++j)
		{
			if (i < 0 || j < 0 || i >= width || j >= heigth)
				continue;
			map[width * i + j].isAttacked = true;
		}
	}

	player.onShipLost(ship);
}

bool ShipField::anyShipsAlive()
{
	for (auto ship : ships)
		if (ship.alive())
			return true;

	return false;
}
