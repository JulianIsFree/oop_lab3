#pragma once
#include <iostream>
#include <memory>
#include <string>

#include "Controller.h"
#include "Viewer.h"

#include "Field.h"

class Event;

class PlayerInterface
{
public:
	//virtual bool onTurn() = 0;
	virtual bool onTurn() = 0;
	virtual bool isDefeated() = 0;
	virtual void onDefeat() = 0;
	virtual void onSurrender() = 0;
	
	virtual bool onAttack(int x, int y) = 0;

	virtual void sendMessage(const std::string &message) = 0;
	
};

class Player : public PlayerInterface
{
protected:
	std::string id;
	bool isBound;
	bool isSurrender;
public:
	Player(const std::string &name) : 
		id(name), isBound(false),
		isSurrender(false) {};

	// returns false is turn is ended
	virtual bool onTurn();
	virtual void onDefeat() { sendMessage(id + " is defeated"); };
	virtual bool isDefeated() { return true; };
	virtual void onSurrender() { isSurrender = true; sendMessage(id + " admits defeat"); };
	virtual void sendMessage(const std::string &message) { std::cout << message << std::endl; };
	virtual bool onAttack(int x, int y) { return false; };

	const std::string& getName() { return id; };
};

class ShipPlayer : public Player
{
private:
	std::shared_ptr<ShipController> controller;
	std::shared_ptr<Viewer> viewer;
	std::shared_ptr<ShipPlayer> oponent;
	ShipField field;
public:
	ShipPlayer(const std::string &name, const std::shared_ptr<ShipController>& controller, 
		const std::shared_ptr<Viewer>& viewer) : Player(name), 
		field(controller->getShips(), *this),
		controller(controller),
		viewer(viewer)
	{};
	virtual void ShipPlayer::bind(const std::shared_ptr<ShipPlayer>& oponent);
	virtual bool onTurn() override;
	virtual bool isDefeated() override;
	virtual void sendMessage(const std::string & message) override { viewer->sendMessage(message); }
	virtual bool onAttack(int x, int y) override { return field.onAttack(x, y); };
	void onShipLost(const Ship& ship);
};
