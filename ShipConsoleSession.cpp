#include <iostream>
#include <string>

#include "optionparser.h"
#include "ShipConsoleSession.h"
#include "Controller.h"
#include "Viewer.h"

#include <chrono>


/*
n 0 0 n 2 0 n 4 0 n 6 0 n 8 0 n 0 8 n 2 9 n 4 9 n 6 9 n 8 9
*/
ShipConsoleSession::ShipConsoleSession(const std::shared_ptr<ShipController>& c1, const std::shared_ptr<ShipController>& c2, 
	const std::shared_ptr<ConsoleViewer>&v1, const std::shared_ptr<ConsoleViewer>&v2, int rounds) :
	Session(rounds),
	p1(std::make_shared<ShipPlayer>("Vanguard", c1, v1)),
	p2(std::make_shared<ShipPlayer>("Solo-ranker", c2, v2))
	{
		srand(time(NULL));
		this->p1->bind(p2);
		this->p2->bind(p1);
	}

////////
void ShipConsoleSession::run()
{
	while (rounds-- > 0)
	{
		p1->sendMessage("Round starts");
		p2->sendMessage("Round starts");

		int turn = 1;
		while (true)
		{
			std::string message = "Turn: " + std::to_string(turn);
			p1->sendMessage(message);
			while (!p2->isDefeated() &&
				p1->onTurn());
			if (p1->isDefeated())
			{
				p1->onDefeat();
				p2->sendMessage("You won");
				break;
			}
			if (p2->isDefeated())
			{
				p2->onDefeat();
				p1->sendMessage("You won");
				break;
			}

			p2->sendMessage("Turn: " + std::to_string(turn));
			while (!p1->isDefeated() &&
				p2->onTurn());
			if (p1->isDefeated())
			{
				p1->onDefeat();
				p2->sendMessage("You won");
				break;
			}
			if (p2->isDefeated())
			{
				p2->onDefeat();
				p1->sendMessage("You won");
				break;
			}

			++turn;
		}
	}

}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	Parser parser(argc, argv);
	//////..
	//////
	if (parser.pars() != 0)
		return 1;

	ShipConsoleSession s(parser.getFirst(), parser.getSecond(), 
		std::make_shared<ConsoleViewer>(), std::make_shared<ConsoleViewer>(),parser.getRounds());
	s.run();

	return 0;//
}

int Parser::pars()
{
	using namespace std;

	argc--;
	argv++;
	enum optionIndex { UNKNOWN, HELP, COUNT, FIRST, SECOND };
	const option::Descriptor usage[] =
	{
		{UNKNOWN, 0, "", "", option::Arg::None, "unknown parameter"},
		{HELP, 0, "h", "help", option::Arg::None, "-h/--help"},
		{COUNT, 0, "c", "count", option::Arg::Optional, "-c/--count=n"},
		{FIRST, 0, "f", "first", option::Arg::Optional, "-f/--first=random/player/optimal"},
		{SECOND, 0, "s", "second", option::Arg::Optional, "-s/--second=random/player/optimal"},
		{0,0,0,0,0,0}
	};

	option::Stats stats(usage, argc, argv);
	option::Option options[5];
	option::Option buffer[5];
	option::Parser parse(usage, argc, argv, options, buffer);

	if (parse.error())
		return 1;

	if (options[HELP])
	{
		option::printUsage(cout, usage);
		return 1;
	}

	if (options[FIRST].count() == 0)
	{
		first = make_shared<RandomShipController>(RandomShipController());
	}
	else
	{
		auto o = options[FIRST].last();
		if (o->arg == nullptr)
			return 1;
		std::string word(o->arg);
		if (word == "=random")
			first = make_shared<RandomShipController>(RandomShipController());
		else if (word == "=player")
			first = make_shared<ExternalShipController>(ExternalShipController());
		else if (word == "=optimal")
			first = make_shared<OptimalShipController>(OptimalShipController());
		else
			return 1;
	}

	if (options[SECOND].count() == 0)
	{
		second = make_shared<RandomShipController>(RandomShipController());
	}
	else
	{
		auto o = options[SECOND].last();
		if (o->arg == nullptr)
			return 1;
		std::string word(o->arg);
		if (word == "=random")
			second = make_shared<RandomShipController>(RandomShipController());
		else if (word == "=player")
			second = make_shared<ExternalShipController>(ExternalShipController());
		else if (word == "=optimal")
			second = make_shared<OptimalShipController>(OptimalShipController());
		else
			return 1;
	}
	
	if (options[COUNT].count() == 0)
	{
		rounds = 1;
	}
	else
	{
		if (options[COUNT].last()->arg == nullptr)
			return 1;

		const char* arg = options[COUNT].last()->arg + 1;
		rounds = atoi(arg);
	}

	return 0;
}

