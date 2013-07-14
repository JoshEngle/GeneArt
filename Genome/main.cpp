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
#include "system.h"


int _tmain(int argc, _TCHAR* argv[])
{
	System* system = new System;

	if(system->Initialize())
		system->Run();

	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}