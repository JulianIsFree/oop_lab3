#include "Logic.h"
#include "Exception.h"

Rectangle::Rectangle(Point p1, Point p2) : width(p2.x - p1.x + 1), heigth(p2.y - p1.y + 1), p1(p1), p2(p2)
{
	if (width <= 0)
		throw BadShipSize("width is less or equal than 0");

	if (heigth <= 0)
		throw BadShipSize("heigth is less or equal than 0");
}

bool Rectangle::isCollision(Point p) const
{
	return (p.x >= p1.x) && (p.x <= p2.x) && (p.y >= p1.y) && (p.y <= p2.y);
}

bool Rectangle::isCollision(const Rectangle & other) const
{
	return other.isCollision(p1) || other.isCollision(p2) ||
		isCollision(other.p1) || isCollision(other.p2);
}

void Rectangle::transport()
{
	std::swap(p2.x, p2.y);
	std::swap(width, heigth);
}

void Rectangle::bind(Point p)
{
	p1 = p;
	p2.x = p1.x + width - 1;
	p2.y = p1.y + heigth - 1;
}

Point randPoint(Point p2, Point p1)
{
	int width = p2.x - p1.x + 1;
	int height = p2.y - p1.y + 1;

	int x = p1.x + rand() % width;
	int y = p1.y + rand() % height;

	return Point(x, y);
}

Point::operator std::string() const
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}