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
ShipConsoleSession::ShipConsoleSession(ShipController & c1, ShipController & c2, ConsoleViewer &v1, ConsoleViewer &v2, int rounds) :
	Session(new ShipPlayer("Vanguard", c1, v1), new ShipPlayer("Solo-rankers", c2, v2), rounds) {	srand(time(NULL));
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	Parser parser(argc, argv);
	////
	if (parser.pars() != 0)
		return 1;
	ShipConsoleSession s(parser.getFirst(), parser.getSecond(), ConsoleViewer(), ConsoleViewer(), parser.getRounds());
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

	if (options[HELP] || argc == 0)
	{
		option::printUsage(cout, usage);
		return 1;
	}

	if (options[FIRST].count() == 0)
	{
		first = make_unique<ShipController*>(new RandomShipController());
	}
	else
	{
		auto o = options[FIRST].last();
		if (o->arg == nullptr)
			return 1;
		std::string word(o->arg);
		if (word == "=random")
			first = make_unique<ShipController*>(new RandomShipController());
		else if (word == "=player")
			first = make_unique<ShipController*>(new ExternalShipController());
		else if (word == "=optimal")
			first = make_unique<ShipController*>(new OptimalShipController());
		else
			return 1;
	}

	if (options[SECOND].count() == 0)
	{
		second = make_unique<ShipController*>(new RandomShipController());
	}
	else
	{
		auto o = options[SECOND].last();
		if (o->arg == nullptr)
			return 1;
		std::string word(o->arg);
		if (word == "=random")
			second = make_unique<ShipController*>(new RandomShipController());
		else if (word == "=player")
			second = make_unique<ShipController*>(new ExternalShipController());
		else if (word == "=optimal")
			second = make_unique<ShipController*>(new OptimalShipController());
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
		try 
		{
			rounds = atoi(options[COUNT].last()->arg);
		}
		catch(std::exception &e)
		{
			return 1;
		}
	}

	return 0;
}

