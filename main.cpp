
#include <iostream>
#include <fstream>
#include "Editor.h"


using namespace std;


int main()
{



	Editor ed;
	
	ed.readFile();
	ed.readKeyWords();
	ed.printLines();
	ed.processCommand();
	
	
	
	return 0;
}

