#pragma once
#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(const std::string & message) : std::exception(message.c_str()) {};
};

class RuleAssertException : public Exception
{
public:
	RuleAssertException(const std::string &what) : Exception("Code exception: " + what) {};
};

class BadShipSize : public RuleAssertException
{
public:
	BadShipSize(const std::string& why) : RuleAssertException("Bad ship size: " + why) {};
};

class BadDamage : public RuleAssertException
{
public:
	BadDamage() : RuleAssertException("can't deal damage to dead object") {};
};