#include <iostream>
#include <string>
#include "Command.h"
using namespace std;

//SETTERS
void Command::setCommand(const string& x) {
	command = x;
}

void Command::setValue(const string& x) {
	value = x;
}

void Command::setLine(const int& x) {
	line = x;
}
void Command::setPosition(const int& x) {
	position = x;
}

//GETTERS
string Command::getCommand() const {
	return command;
}

string Command::getValue() const {
	return value;
}

int Command::getLine() const {
	return line;
}
int Command::getPosition() const {
	return position;
}
//CONSTRUCTORS
Command::Command() {
	command = "";
	value = "";
	line = 0;
	position = 0;
}

Command::Command(const string& c) {
	command = c;
}

Command::Command(const string& c, const string& v) {
	command = c;
	value = v;
}

Command::Command(const string& c, const string& v, const int& l) {
	command = c;
	value = v;
	line = l;
}

Command::Command(const string& c, const string& v, const int& l, const int& p) {
	command = c;
	value = v;
	line = l;
	position = p;
}

