#pragma once
#include "Exception.h"

class PlayerException : Exception
{
public:
	PlayerException(const std::string& why) : Exception("Player exception: " + why) {};
};

class PlayerBoundException : PlayerException
{
public:
	PlayerBoundException(const std::string& id, const std::string& oponentId) : PlayerException("player " + id + " is already bound with " + oponentId) {};
};

class PlayerNotBoundException : PlayerException
{
public:
	PlayerNotBoundException(const std::string& id, const std::string& what) : PlayerException("player isn't bound, " + what) {};
};
