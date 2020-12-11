#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "ArrayStack.h"
#include "Command.h"
#include "BinarySearchTree.h"

using namespace std;

class Editor {
private:
	int currentLine;
	int currentPosition;
	int numLines;
	BinarySearchTree<string>* keyTree;

	Command tempCommand; //to push to commandStack
	ArrayStack<Command> commandStack;

	ifstream inFile;
	LinkedList<string> fileList;

public:

	void readFile();
	void printLines() const; //prints linked list with carats at line and position
	void processCommand();
	void readKeyWords() ;
	
	Editor();

};


