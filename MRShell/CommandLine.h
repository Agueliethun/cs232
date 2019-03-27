/*
 * CommandLine.h
 *
 *  Created on: Feb 23, 2018
 *  Course: CS 232 at Calvin College
 *  Author: Matthew Nykamp (mrn6)
 *
 *  CommandLine is a class which facilitates reading in arguments
 *  from the command line, designed for the shell MRShell
 */

#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_

#include <exception>
#include <iostream>
#include <stdlib.h>
using namespace std;

class CommandLine {
public:
	CommandLine(istream& in);
	char* getCommand() const;
	int getArgCount() const {return argc;}
	char** getArgVector() const;
	char* getArgVector(int i) const;
	bool noAmpersand() const;
	~CommandLine();
private:
	int argc;
	char** argv;
};

#endif /* COMMANDLINE_H_ */
