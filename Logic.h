#pragma once
#include <string>
#include <cstdlib>

class Entity
{
protected:
	bool isAlive;
public:
	Entity(bool isAlive=false) : isAlive(isAlive) {};
	virtual void onDamage() {};
	virtual void onDeath() { isAlive = false; };
	bool alive() const { return isAlive; };
};

class Shape {};

class Point
{
public:
	int x;
	int y;
	Point(int x, int y) : x(x), y(y) {};
	Point() : x(0), y(0) {};
	operator std::string() const;
};

Point randPoint(Point p2, Point p1 = { 0,0 });

class Rectangle : public Shape
{
protected:
	int width;
	int heigth;
	Point p1, p2; // TODO: remove p2
public:
	Rectangle(int width, int height) : p1({ 0, 0 }), p2({ width - 1, height - 1 }), width(width), heigth(height) {};
	Rectangle(Point p1, Point p2);
	Rectangle(Point p1, int width, int heigth) : p1(p1), p2(p1), width(width), heigth(heigth) {};

	bool isCollision(Point p) const;
	bool isCollision(const Rectangle& other) const;

	int getWidth() const { return width; };
	int getHeigth() const { return heigth; };
	
	Point getP1() { return p1; };
	Point getP2() { return p2; };

	void transport();
	void bind(Point p); // putting bottom-left angle of rectangle in the point p
};
