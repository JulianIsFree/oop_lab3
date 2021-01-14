#pragma once
#include <iostream>
#include <string>

class Viewer
{
public:
	virtual void sendMessage(const std::string& message) {};
};

class ConsoleViewer : public Viewer
{
public:
	virtual void sendMessage(const std::string& message) { std::cout << message << std::endl; };
};
