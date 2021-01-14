#include <iostream>

#include "Player.h"
#include "PlayerException.h"
#include "LogicException.h"
#include "Event.h"

#include "Session.h"

void Player::bind(Player * oponent)
{
	if (isBound)
		throw PlayerBoundException(id, (*this->oponent)->id);
	
	isBound = true;
	this->oponent = std::make_shared<Player*>(oponent);
}

bool Player::onTurn()
{
	sendMessage(id + " does nothing");
	return false;
}

bool ShipPlayer::onTurn()
{
	sendMessage(id + "'s turn");
	if (!isBound)
		throw PlayerNotBoundException(id, "no target for event");

	try
	{
		std::unique_ptr<Event*> e = controller.onTurn();
		(*e)->run(*this, **oponent);
	}
	catch(LogicException& e)
	{
		sendMessage(e.what());
		return true;
	}
	catch (Exception& e)
	{
		sendMessage(e.what());
		sendMessage(id + ": critical error");
	}

	return false;
}

bool ShipPlayer::isDefeated()
{
	return !field.anyShipsAlive() || isSurrender;
}

void ShipPlayer::onShipLost(const Ship & ship)
{
	this->sendMessage("You lost object: " + std::string(ship));
	(*oponent)->sendMessage("Enemy lost object: " + std::string(ship));
}
