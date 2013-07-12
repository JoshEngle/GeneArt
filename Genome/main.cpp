////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
//
// JOP
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <math.h>
#include "Genome.h"


#define PRINT			"print"
#define LOAD			"load"
#define HELP			"help"
#define QUIT			"quit"

bool ExecuteCommand(string* commands, int commandCount, Genome* genome) // Command Line
{
	cout << "\n";

	// Convert to Lower case.
	for(int i = 0; i < commandCount; i++)
	{
		std::transform(commands[i].begin(), commands[i].end(), commands[i].begin(), ::tolower);
	}

	if(commands[0] == HELP)
	{
		cout << "COMMAND LIST";
		cout << "\nLOAD FILE\t\tLoad a plain text file.";
		cout << "\nPRINT NUMBER\t\tPrint every % NUMBER.";
		cout << "\nQUIT\t\t\tExit the application.";
	}
	else if(commands[0] == LOAD)
	{
		if(genome->LoadFromTextFile((char*)commands[1].c_str()))
		{
			cout << "SUCCESS!!!";
		}
		else
		{
			cout << "Unable to load file!";
		}
	}
	else if(commands[0] == PRINT)
	{
		if(IsNumber(commands[1]))
			genome->Print(stoi(commands[1]));
	}
	else if(commands[0] == QUIT)
	{
		return true;
	}
	else
	{
		cout << "\n\nTry that again. Help lists available commands.";
	}

	cout << "\n\n> ";

	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "The Genome Project\n\n";
	cout <<	"\n\n\nEnter a command. Type help for a list of commands.\n\n> ";

	Genome* genome = new Genome;

	bool done = false;
	while(!done)
	{
		string input;
		string command[2]	= {"", ""};

		getline(cin, input);

		// Break apart commands.
		istringstream iss(input);
		int i = 0;
		while(iss)
		{
			iss >> command[i++];
		}

		i--;

		// If ExecuteCommand returns true the user has quit.
		done = ExecuteCommand(command, i, genome);
	}

	genome->Shutdown();
	delete genome;
	genome = 0;

	return 0;
}