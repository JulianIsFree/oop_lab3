#include "Ship.h"
#include "Exception.h"

Rectangle Ship::getOrion() const
{
	return Rectangle({ p1.x - 1, p1.y - 1 }, { p2.x + 1, p2.y + 1 });
}

bool Ship::isCollision(const Ship & other) const
{
	return getOrion().isCollision(other);
}

void Ship::onDamage()
{
	if (hp <= 0)
		throw BadDamage();

	if (--hp <= 0)
		onDeath();
}

Ship::operator std::string() const
{
	return "Ship: " + name + " is at " + std::string(p1) + "::" + std::string(p2) + "now";
}
