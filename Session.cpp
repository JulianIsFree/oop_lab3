#include <string>

#include "Session.h"
#include "Controller.h"
#include "Viewer.h"
#include "Event.h"
#include "Player.h"

Session::Session(Player *p1, Player *p2, int rounds) :
	p1(std::make_shared<Player*>(p1)),
	p2(std::make_shared<Player*>(p2)),
	rounds(rounds)
{
	p1->bind(p2);
	p2->bind(p1);
}

void Session::run()
{
	while (rounds--)
	{
		(*p1)->sendMessage("Round starts");
		(*p2)->sendMessage("Round starts");

		int turn = 1;
		while (true)
		{
			std::string message = "Turn: " + std::to_string(turn);
			(*p1)->sendMessage(message);
			while (!(*p2)->isDefeated() &&
				(*p1)->onTurn());
			if ((*p1)->isDefeated())
			{
				(*p1)->onDefeat();
				(*p2)->sendMessage("You won");
				break;
			}
			if ((*p2)->isDefeated())
			{
				(*p2)->onDefeat();
				(*p1)->sendMessage("You won");
				break;
			}

			(*p2)->sendMessage("Turn: " + std::to_string(turn));
			while (!(*p1)->isDefeated() &&
				(*p2)->onTurn());
			if ((*p1)->isDefeated())
			{
				(*p1)->onDefeat();
				(*p2)->sendMessage("You won");
				break;
			}
			if ((*p2)->isDefeated())
			{
				(*p2)->onDefeat();
				(*p1)->sendMessage("You won");
				break;
			}
			++turn;
		}
	}
	
}
