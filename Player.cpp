#include <iostream>

#include "Player.h"
#include "PlayerException.h"
#include "LogicException.h"
#include "Event.h"

#include "Session.h"

void ShipPlayer::bind(const std::shared_ptr<ShipPlayer>& oponent)
{
	if (isBound)
		throw PlayerBoundException(id, this->oponent->getName());
	
	isBound = true;
	this->oponent = oponent;
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
		//ShipController & c = dynamic_cast<ShipController&>(*controller);
		ShipController *c = &(*controller);
		std::shared_ptr<Event> e = c->onTurn();
		e->run(*this, *oponent);
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
	oponent->sendMessage("Enemy lost object: " + std::string(ship));
}
