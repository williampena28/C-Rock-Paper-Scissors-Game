#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "Header.h"

void GameManager::ErrorPrint()
{
	std::cout << "ERROR:" << "\t BAD COMMAND!!!" << std::endl;
}

choice ComputerChoice() //Helper function that returns a choice (the computer's choice) to be compared to the player's choice later on
{
	choice ComputerChoice;

	std::random_device rd; //generate random number
	std::mt19937 gen(rd()); //seed the generator
	std::uniform_int_distribution<> distr(1, 3); //define the range from 1 to 3

	if (distr(gen) == 1)
	{
		ComputerChoice = choice::rock;
		return ComputerChoice;
	}
	else if (distr(gen) == 2)
	{
		ComputerChoice = choice::paper;
		return ComputerChoice;
	}
	else if (distr(gen) == 3)
	{
		ComputerChoice = choice::scissors;
		return ComputerChoice;
	}
}

choice Player::GetChoice()
{
	return PlayerChoice;
}

void Player::SetChoice(const std::string& PlayerInput)
{
	if (PlayerInput == "rock")
	{
		PlayerChoice = choice::rock;
	}
	else if (PlayerInput == "paper")
	{
		PlayerChoice = choice::paper;
	}
	else if (PlayerInput == "scissors")
	{
		PlayerChoice = choice::scissors;
	}
}

std::vector<std::string> MyParser::operator() (const std::string& command)
{
	std::vector<std::string> parsed_command; //parsed command
	if (command.empty())
	{
		return parsed_command;
	}
	int check = 0; //check for " " characters to not be included in the vector
	bool name_check = false; //Check for name strings to not be parsed

	std::string token; //add characters until " " then add the string to vector

	for (int i = 0; i < command.length(); i++)
	{
		if (command.at(i) == '"' && name_check == false)
		{
			name_check = !name_check;

		}
		else if (command.at(i) == '"' && name_check == true)
		{
			name_check = !name_check;
			token.push_back(command.at(i));
			parsed_command.push_back(token);
			check = 0;
			token = "";
		}

		if (((command.at(i) >= 'a' && command.at(i) <= 'z') || (command.at(i) >= 'A' && command.at(i) <= 'Z') || (command.at(i) >= '0' && command.at(i) <= '9') || command.at(i) >= '<' && command.at(i) <= '>') && name_check == false)
		{
			token.push_back(command.at(i));
			check++;
		}
		else if (((command.at(i) == MyParser::separators[0] || command.at(i) == MyParser::separators[1]) && check > 0) && name_check == false)
		{
			parsed_command.push_back(token);
			check = 0;
			token = "";
		}
		else if (name_check == true)
		{
			token.push_back(command.at(i));
		}
	}

	if (token != "")
	{
		parsed_command.push_back(token);
	}

	return parsed_command;
}

void GameManager::FindWinner(Player& Human)
{
	choice Computer = ComputerChoice();
	choice Player = Human.GetChoice();

	switch (Computer)
	{
	case choice::rock:
		if (Player == choice::rock) //Draw
		{
			std::cout << "\nYou picked: rock" << "\t" << "CPU picked: rock" << std::endl;
			std::cout << "DRAW!" << std::endl;
		}
		else if (Player == choice::paper)//Win
		{
			std::cout << "\nYou picked: paper" << "\t" << "CPU picked: rock" << std::endl;
			std::cout << "YOU WIN!" << std::endl;
		}
		else if (Player == choice::scissors)//Lose
		{
			std::cout << "\nYou picked: scissors" << "\t" << "CPU picked: rock" << std::endl;
			std::cout << "YOU LOSE!" << std::endl;
		}
		break;

	case choice::paper:
		if (Player == choice::rock) //Lose
		{
			std::cout << "\nYou picked: rock" << "\t" << "CPU picked: paper" << std::endl;
			std::cout << "YOU LOSE!" << std::endl;
		}
		else if (Player == choice::paper)//Draw
		{
			std::cout << "\nYou picked: paper" << "\t" << "CPU picked: paper" << std::endl;
			std::cout << "DRAW!" << std::endl;
		}
		else if (Player == choice::scissors)//Win
		{
			std::cout << "\nYou picked: scissors" << "\t" << "CPU picked: paper" << std::endl;
			std::cout << "YOU WIN!" << std::endl;
		}
		break;

	case choice::scissors:
		if (Player == choice::rock) //WIN
		{
			std::cout << "\nYou picked: rock" << "\t" << "CPU picked: scissors" << std::endl;
			std::cout << "YOU WIN!" << std::endl;
		}
		else if (Player == choice::paper)//LOSE
		{
			std::cout << "\nYou picked: paper" << "\t" << "CPU picked: scissors" << std::endl;
			std::cout << "YOU LOSE!" << std::endl;
		}
		else if (Player == choice::scissors)//DRAW
		{
			std::cout << "\nYou picked: scissors" << "\t" << "CPU picked: scissors" << std::endl;
			std::cout << "DRAW!" << std::endl;
		}
		break;
	}

}

bool GameManager::process(const std::vector<std::string>& ParsedInput)
{
	if (ParsedInput[0] == "PLAY" && (ParsedInput[1] == "rock" || ParsedInput[1] == "paper" || ParsedInput[1] == "scissors"))
	{
		Player Human;
		Human.SetChoice(ParsedInput[1]);
		GameManager::FindWinner(Human);
		std::cout << "\n" << "Play again?" << std::endl;

		return false;
	}
	else if (ParsedInput[0] == "STOP") //terminates the program
	{
		return true;
	}
	else if (ParsedInput[0] != "STOP" && ParsedInput[0] != "PLAY")
	{
		GameManager::ErrorPrint();
		return false;
	}
	else if (ParsedInput[0] == "PLAY" && (ParsedInput[1] != "rock" || ParsedInput[1] != "paper" || ParsedInput[1] != "scissors"))
	{
		GameManager::ErrorPrint();
		return false;
	}
}

int main()
{
	GameManager engine;
	MyParser parser;

	std::string UserInput;
	bool terminate = false;

	std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
	std::cout << "*                 ROCK, PAPER, SCISSORS!              *" << std::endl;
	std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;

	while (!terminate)
	{
		getline(std::cin, UserInput);
		terminate = engine.process(parser(UserInput));
	}

	return 0;
}
