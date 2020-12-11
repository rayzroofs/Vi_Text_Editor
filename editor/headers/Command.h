#include <iostream>
#include <string>

using namespace std;

class Command {
public:
	void setCommand(const string&);
	void setValue(const string&);
	void setLine(const int&);
	void setPosition(const int&);

	string getCommand() const;
	string getValue() const;
	int getLine() const;
	int getPosition() const;

	Command();
	Command(const string& c);
	Command(const string& c, const string& v);
	Command(const string& c, const string& v, const int& z);
	Command(const string& c, const string& v, const int& z, const int& p);
private:
	string command;
	string value;
	int line;
	int position;
};