#pragma once
#include <memory>

#include "Session.h"
#include "Player.h"
#include "Viewer.h"
#include "Controller.h"

class ShipConsoleSession : public Session
{
public:
	ShipConsoleSession(ShipController & c1, ShipController & c2, ConsoleViewer &v1, ConsoleViewer &v2, int rounds);
};

class Parser
{
	std::unique_ptr<ShipController*> first;
	std::unique_ptr<ShipController*> second;
	int rounds;
	int argc;
	char **argv;
public:
	Parser(int argc, char **argv) : argc(argc), argv(argv), rounds(0) {};
	int pars();

	ShipController & getFirst() const { return **first; };
	ShipController & getSecond() const { return **second; };
	int getRounds() { return rounds; };
};