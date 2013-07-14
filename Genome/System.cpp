#include "system.h"

#define PRINT			"print"
#define LOAD			"load"
#define HELP			"help"
#define QUIT			"quit"


System::System()
{
	m_genome = 0;
}

System::~System()
{

}

bool System::Initialize()
{
	m_genome = new Genome;

	return true;
}

void System::Shutdown()
{
	if(m_genome)
	{
		m_genome->Shutdown();
		delete m_genome;
		m_genome = 0;
	}
}

void System::Run()
{
	cout << "The Genome Project\n\n";
	cout <<	"\n\n\nEnter a command. Type help for a list of commands.\n\n> ";

	bool done = false;
	while(!done)
	{
		string input;
		string command[2]	= {"", ""};

		getline(cin, input);

		// Break apart commands.
		istringstream iss(input);
		int i = 0;
		while(iss && i < 2)
		{
			iss >> command[i++];
		}

		i--;

		// If ExecuteCommand returns true the user has quit.
		done = ExecuteCommand(command, i);
	}
}

bool System::ExecuteCommand(string* commands, int commandCount)
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
		if(m_genome->LoadFromTextFile((char*)commands[1].c_str()))
		{
			cout << "File loaded.";
		}
		else
		{
			cout << "Unable to load file!";
		}
	}
	else if(commands[0] == PRINT)
	{
		if(IsNumber(commands[1]))
			m_genome->Print(stoi(commands[1]));
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