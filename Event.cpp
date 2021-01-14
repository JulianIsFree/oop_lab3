#include <string>

#include "Event.h"
#include "Player.h"
#include "Logic.h"

void AttackEvent::run(Player & p, Player & t) const
{
	t.sendMessage(p.getName() + " attacking " + std::string(target));
	if (t.onAttack(target.x, target.y))
	{
		t.sendMessage(p.getName() + " damaged ship at " + std::string(target));
		p.sendMessage("you damaged ship at " + std::string(target));
		while (!t.isDefeated() && p.onTurn());
	}
		
}

void SurrenderEvent::run(Player & p, Player & t) const
{
	p.onSurrender();
	t.sendMessage(p.getName() + " admits defeat");
}
