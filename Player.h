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
	Controller &controller;
	Viewer &viewer;
	std::string id;
	std::shared_ptr<Player*> oponent;

	bool isBound;
	bool isSurrender;
public:
	Player(const std::string &name, Controller& controller, Viewer& viewer) : id(name), isBound(false),
		controller(controller), viewer(viewer), isSurrender(false) {};
	void bind(Player* oponent);

	// returns false is turn is ended
	virtual bool onTurn();
	virtual void onDefeat() { sendMessage(id + " is defeated"); };
	virtual bool isDefeated() { return true; };
	virtual void onSurrender() { isSurrender = true; sendMessage(id + " admits defeat"); };
	virtual void sendMessage(const std::string &message) { viewer.sendMessage(message); };
	virtual bool onAttack(int x, int y) { return false; };

	const std::string& getName() { return id; };
};

class ShipPlayer : public Player
{
private:
	ShipField field;
public:
	ShipPlayer(const std::string &name, ShipController& controller, Viewer& viewer) : Player(name, controller, viewer), field(controller.getShips(), *this) {};
	virtual bool onTurn() override;
	virtual bool isDefeated() override;
	virtual bool onAttack(int x, int y) override { return field.onAttack(x, y); };
	void onShipLost(const Ship& ship);
};
