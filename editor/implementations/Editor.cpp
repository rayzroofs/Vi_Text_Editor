#include "Editor.h"
#include "LinkedList.h"
#include "ArrayStack.h"
#include <iostream>
#include <conio.h>
#include <string>
#include "windows.h"
#include <sstream>
#include <vector>
#include "BinarySearchTree.h"
#include <iterator>

using namespace std;

Editor::Editor() {
	currentLine = 1;
	currentPosition = 1; //position 2 because ^(cursor) will be one space over
	numLines = 0;
	keyTree = new BinarySearchTree<string>();
}

void Editor::readFile() {
	inFile.open("test.txt");
	if (!inFile) {
		cout << "Error: no file." << endl;
		return;
	}
	else {
		string tempS;
		
		for (int i = 1; !inFile.eof(); i++) {
			getline(inFile, tempS);
			fileList.insert(i, tempS);
			
		}
		numLines = fileList.getLength();
	}
}


/*
void Editor::printLines() {
	int i, j;
	for (i = 1; i <= fileList.getLength(); i++) {
		if (i == currentLine) {
			cout << "^" << fileList.getEntry(i) << endl;
			for (j = 1; j < currentPosition; j++) {
				cout << " ";
			}
			cout << "^" << endl;
		}
		else
			cout << " " << fileList.getEntry(i) << endl;
	}
}
*/

void Editor::processCommand() {
	
	char ch;
	do {
		
		ch = _getch();
		ch = tolower(ch);
		switch (ch) {
		// MOVE CURSOR DOWN
		case 'j': 
			if (currentLine < fileList.getLength()) {

				if (currentPosition <= fileList.getEntry(currentLine + 1).length())
					currentLine++; //down
				else if (currentPosition > fileList.getEntry(currentLine + 1).length()) {
					currentPosition = fileList.getEntry(currentLine + 1).length() + 1;
					//+1 because starting position = 2
					currentLine++;
				}

			}

			else if (currentLine== fileList.getLength())
				currentLine = currentLine+1;

			break;

		// MOVE CURSOR UP 
		case 'k': if (currentLine > 1) {
			if (currentPosition <= fileList.getEntry(currentLine - 1).length())
				currentLine--; //up
			else if (currentPosition > fileList.getEntry(currentLine - 1).length()) {
				currentPosition = fileList.getEntry(currentLine - 1).length() + 1;
				currentLine--;
			}
		}
				  else
			currentLine = currentLine;

			break;
		// MOVE CURSOR LEFT
		case 'h':if (currentPosition > 1)
			currentPosition--; //left
				 else
			currentPosition = currentPosition;

			break;
		// MOVE CURSOR RIGHT
		case 'l':
			if (currentPosition < fileList.getEntry(currentLine).length())
				
				currentPosition++; //right
			else
				currentPosition = currentPosition;
			break;

		// DD DELETES LINE
		case 'd': 
			ch = _getch();
			//ch = _getch();	//on different system testing I required second _getche(), I think '\n' was left in the input buffer, uncertain of issue

			ch = tolower(ch);
			if (ch == 'd' && currentLine<=fileList.getLength()) {//current line check so can't non-exiline
				tempCommand.setCommand("dd");
				tempCommand.setValue(fileList.getEntry(currentLine));
				tempCommand.setLine(currentLine);
				commandStack.push(tempCommand); //push to stack

				fileList.remove(currentLine); //removes desired line
				numLines--; //dec count of lines
				if (currentLine == fileList.getLength() + 1) //so final line isn't blank
					currentLine--;

			}
		
			break;
		
		// INSERT MODE
		case 'i': {
			
			string insertValue = "";
			getline(cin, insertValue);
			
			tempCommand.setCommand("i");
			tempCommand.setValue(insertValue);
			tempCommand.setLine(currentLine);
			commandStack.push(tempCommand); //push to stack

			fileList.insert(currentLine, insertValue); //insert the input string to the list
			//currentPosition = insertValue.length(); //setting position for formatting the print
			numLines++; //inc num count
		}
			break;

		// DELETE CHARACTER
		case 'x':
		{
			tempCommand.setCommand("x");
			tempCommand.setValue(fileList.getEntry(currentLine));
			tempCommand.setLine(currentLine);
			commandStack.push(tempCommand);

			string currentString = fileList.getEntry(currentLine);
			currentString.erase(currentPosition-1, 1);
			fileList.remove(currentLine);
			fileList.insert(currentLine,currentString);
		}
			break;

		// UNDO last command
		case 'u': {
			if (!commandStack.isEmpty()) { //only undo if stack not empty
				tempCommand = commandStack.peek();
				if (tempCommand.getCommand() == "i") {
					fileList.remove(tempCommand.getLine());
					numLines--; //dec count

					//formatting to retain current line
					if (currentLine > fileList.getLength())
						currentLine--;
				}
				else if (tempCommand.getCommand() == "dd") {
					fileList.insert(tempCommand.getLine(), tempCommand.getValue());
					numLines++; //inc count
				}

				else if (tempCommand.getCommand() == "x") {
					fileList.remove(tempCommand.getLine());
					fileList.insert(tempCommand.getLine(), tempCommand.getValue());
				}
				commandStack.pop();
			}
		}
		default: currentLine = currentLine;
			currentPosition = currentPosition;
			break;
		}
		system("cls");
		printLines();

	} while (ch != 27);
	
	// j down, k up, h left, l right



}


void display(string& x) {
	cout << x << endl;
}

void Editor::readKeyWords() {
	ifstream inFile;

	inFile.open("keywords.txt");
	if (!inFile) {
		cout << "missing file";
		return;
	}

	//BinarySearchTree<string> keyTree;
	string keyTerm;

	//filling tree
	while (!inFile.eof()) {
		inFile >> keyTerm;
		keyTree->add(keyTerm);
	}

	inFile.close();
	//keyTree->inorderTraverse(display); //displaying tree in sorted order

}

void goToXY(int column, int line) {

	COORD coord;

	coord.X = column;

	coord.Y = line;

	SetConsoleCursorPosition(

		GetStdHandle(STD_OUTPUT_HANDLE),

		coord);

}

void colorText(int value) {

	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, value);

}

//This method prints the text in buffer

// It will print keywords in blue

// and have a cursor thing that follows you as you navigate



void Editor::printLines() const {

	string myLine;

	int i, j;

	for (i = 1; i < numLines + 1; i++) {

		myLine = fileList.getEntry(i);

		/*if (i == _currentLine){

		//cout << "^" << myLine << endl;

		for (j = 1; j <= _currentPos; j++){

		cout << " ";

		}

		//cout << "^" << endl;

		}

		else

		cout << " " << myLine << endl;

		*/



		istringstream streamWords{ myLine };

		vector<string> words{
			istream_iterator<string>(streamWords), istream_iterator<string>()
		};

		bool isKeyword;

		for (string currentWord : words) {

			isKeyword = keyTree->contains(currentWord);

			if (isKeyword)

				//colorText(FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | 0X80);  //blue
				colorText(0XF0);


			else
				colorText(FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | 0X80);
				//colorText(0XF0);

			//note: updated to remove the extra blanks

			if (currentPosition == 0)

				cout << currentWord;

			else

				cout << " " << currentWord;

		}

		cout << endl;

	}

	goToXY(currentPosition, currentLine - 1);

}
