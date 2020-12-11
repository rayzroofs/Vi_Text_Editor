#pragma once
#ifndef PRECOND_VIOLATED_EXCEPT_
#define PRECOND_VIOLATED_EXCEPT_
#include <stdexcept>
#include <string> // For string data type

using namespace std;

class PrecondViolatedExcept : public logic_error
{
public:
	PrecondViolatedExcept(const string& message = "");
}; // end PrecondViolatedExcept.h
#endif

