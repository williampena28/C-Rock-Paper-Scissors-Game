#pragma once

enum class choice
{
	rock, paper, scissors
};

class Player
{
private:
	choice PlayerChoice;

public:
	choice GetChoice();
	void SetChoice(const std::string& PlayerInput);
};

class MyParser
{
public:
	std::vector<std::string> operator() (const std::string& command); //parses user input and returns a list of tokens
	std::vector<char> separators{ ' ', '\t' };
};

class GameManager
{
public:
	bool process(const std::vector<std::string>& ParsedInput);
	static void FindWinner(Player& Human);
	bool STOP();
	static void ErrorPrint();
};
