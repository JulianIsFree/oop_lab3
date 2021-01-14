#include <iostream>
#include "Controller.h"
#include "Event.h"

#include "Ship.h"

std::unique_ptr<Event*> Controller::onTurn()
{
	return std::make_unique<Event*>(new Event());
}
void RandomShipController::generateAttackSequence()
{
	Point * subArr = new Point[fieldW * fieldH];
	for (int i = 0; i < fieldW; ++i)
		for (int j = 0; j < fieldH; ++j)
			subArr[i*fieldW + j] = Point(i, j);

	const int size = fieldW * fieldH;
	for (int i = 0; i < size - 1; ++i)
	{
		int index = i + rand() % (size - i);
		std::swap(subArr[index], subArr[i]);
		attackSequence.push_back(subArr[i]);
	}
	attackSequence.push_back(subArr[size - 1]);

	delete subArr;
}

void RandomShipController::generateShipPosition()
{
	ships.clear();
	std::vector<Ship> army = 
	{
		BattleShip(), 
		Cruiser(), 
		Cruiser(), 
		Destroyer(),
		Destroyer(),
		Destroyer(),
		Boat(),
		Boat(),
		Boat(),
		Boat()
	};

	for (auto ship : army)
	{
		while (true)
		{
			bool isSuccess = true;
			if (rand() & 1)
				ship.transport();

			Point p = randPoint({ fieldW - ship.getWidth(), fieldH - ship.getHeigth() });
			ship.bind(p);

			for (auto s : ships)
				isSuccess &= !s.isCollision(ship);

			if (isSuccess)
				break;
		}

		ships.push_back(ship);
	}
}

std::unique_ptr<Event*> RandomShipController::onTurn()
{
	if (attackSequence.empty())
		generateAttackSequence();

	Point p = attackSequence[attackSequence.size() - 1];
	attackSequence.pop_back();

	return std::make_unique<Event*>(new AttackEvent(p));
}

void ExternalShipController::generateShipPosition()
{
	ships.clear();
	std::vector<Ship> army =
	{
		BattleShip(),
		Cruiser(),
		Cruiser(),
		Destroyer(),
		Destroyer(),
		Destroyer(),
		Boat(),
		Boat(),
		Boat(),
		Boat()
	};

	for (auto ship : army)
	{
		int x, y;
		std::string rotate;
		std::cout << std::string(ship) << std::endl;

		while (true)
		{
			bool isSuccess = true;

			std::cout << "Rotate? (y/n) ";
			std::cin >> rotate;
			if (rotate == "y")
				ship.transport();
			std::cout << "Ship is " << (rotate == "y" ? "horisontal" : "vertical") << "-oriented" << std::endl;
			std::cout << "Enter pair x, y with space between: ";
			
			std::cin >> x;
			std::cin >> y;
			ship.bind(Point(x, y));
			if (x < 0 || x > fieldW - ship.getWidth() || y < 0 || y > fieldH - ship.getHeigth())
			{
				isSuccess = false;
			}
			else
			{
				for (auto s : ships)
				{
					if (s.isCollision(ship))
					{
						isSuccess = false;
						break;
					}
				}
			}

			if (isSuccess)
				break;
			else	
				std::cout << "Bad position" << std::endl;
		}

		ships.push_back(ship);
	}
}

std::unique_ptr<Event*> ExternalShipController::onTurn()
{
	std::cout << "Enter \"attack x y\" or \"surrender\": ";
	std::string word;
	std::cin >> word;
	if ("attack" == word)
	{
		int x, y;
		std::cin >> x >> y;
		return std::make_unique<Event*>(new AttackEvent(Point(x, y)));
	}
	else if ("surrender" == word)
	{
		std::string why;
		std::cout << "Enter reason: " << std::endl;
		std::cin >> why;
		return std::make_unique<Event*>(new SurrenderEvent(why.empty() ? "no reason" : why));
	}
	else
		return onTurn();
}

bool OptimalShipController::canPlase(const Ship & ship)
{
	for (auto s : ships)
	{
		if (s.isCollision(ship))
			return false;
	}

	return true;
}

bool OptimalShipController::tryPlaseHorisontalLine(Ship & ship, const int y)
{
	for (int x = 0; x < 10; ++x)
	{
		ship.bind(Point(x, y));
		if (canPlase(ship))
			return true;
	}

	return false;
}

bool OptimalShipController::tryPlaseVerticalLine(Ship & ship, const int x)
{
	for (int y = 0; y < 10; ++y)
	{
		ship.bind(Point(x, y));
		if (canPlase(ship))
			return true;
	}

	return false;
}

void OptimalShipController::allocateBigShips()
{
	std::vector<Ship> army =
	{
		BattleShip(),
		Cruiser(),
		Cruiser(),
		Destroyer(),
		Destroyer(),
		Destroyer(),
	};

	for (auto ship : army)
	{
		bool horisontal = false;
		while (true)
		{
			bool isRotate = rand() % 2 == 0;
			if (horisontal)
			{
				horisontal = !horisontal;
				ship.transport();
			}


			int width = ship.getWidth();
			int heigth = ship.getHeigth();

			std::vector<Point> points =
			{
				Point(0,0),
				Point(0, fieldW - width),
				Point(fieldH - heigth, 0),
				Point(fieldH - heigth, fieldW - width)
			};

			bool isSuccess;
			for (auto p : points)
			{
				isSuccess = true;
				ship.bind(p);
				if (!canPlase(ship))
					isSuccess = false;
			}

			if (!isSuccess)
			{
				if (horisontal)
				{
					isSuccess = tryPlaseHorisontalLine(ship, 0);
					if (!isSuccess)
						isSuccess = tryPlaseHorisontalLine(ship, 9);
				}
				else
				{
					isSuccess = tryPlaseVerticalLine(ship, 0);
					if (!isSuccess)
						isSuccess = tryPlaseVerticalLine(ship, 9);
				}
			}

			if (isSuccess)
				break;
		}
		ships.push_back(ship);
	}
}

void OptimalShipController::allocateLittleShips()
{
	std::vector<Ship> army =
	{
		Boat(),
		Boat(),
		Boat(),
		Boat()
	};

	for (auto ship : army)
	{
		while (true)
		{
			int x = 1 + (rand() % 8);
			int y = 1 + (rand() % 8);

			ship.bind(Point(x, y));
			if (canPlase(ship))
				break;
		}
	}
}

void OptimalShipController::generateShipPosition()
{
	ships.clear();
	allocateBigShips();
	allocateLittleShips();
}
