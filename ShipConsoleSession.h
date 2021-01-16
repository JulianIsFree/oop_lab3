#pragma once
#include <memory>

#include "Session.h"
#include "Player.h"
#include "Viewer.h"
#include "Controller.h"

class ShipConsoleSession : public Session
{
	std::shared_ptr<ShipPlayer> p1, p2;

public:
	ShipConsoleSession(const std::shared_ptr<ShipController>& c1, const std::shared_ptr<ShipController>& c2,
		const std::shared_ptr<ConsoleViewer>&v1, const std::shared_ptr<ConsoleViewer>&v2, int rounds);
	virtual void run() override;
};

class Parser
{
	std::shared_ptr<ShipController> first;
	std::shared_ptr<ShipController> second;
	int rounds;
	int argc;
	char **argv;
public:
	Parser(int argc, char **argv) : argc(argc), argv(argv), rounds(0) {};
	int pars();

	const std::shared_ptr<ShipController>& getFirst() const { return first; };
	const std::shared_ptr<ShipController>& getSecond() const { return second; };
	int getRounds() { return rounds; };
};