/*
 * CommandLine.cpp
 *
 *  Created on: Feb 23, 2018
 *  Course: CS 232 at Calvin College
 *  Author: Matthew Nykamp (mrn6)
 *
 *  CommandLine is a class which facilitates reading in arguments
 *  from the command line, designed for the shell MRShell
 */

#include "CommandLine.h"

/*
 * CommandLine initializes the command line
 * setting the argc to be the number of commands given
 * and storing each argument in a c style string inside argv
 */
CommandLine::CommandLine(istream& in) {
	string readIn;
	argc = 0;

	// Loop through to count arguments
	while (!in.eof()) {
		string argument;
		getline(in, argument, ' ');
		argc++;
	}

	// Return to beginning of stream
	in.seekg(0, in.beg);

	// Allocate argv now that we know what the size will be
	argv = (char**) calloc(argc + 1, sizeof(char*));

	//Declare a temp variable we will use as loop index
	int index = 0;

	// For each argument
	while (!in.eof()) {
		// Read in the next section of text until a space is found
		getline(in, readIn, ' ');

		// Allocate the necessary memory, the length of the string
		argv[index] = (char*) calloc(readIn.length() + 1, sizeof(char));

		// Copy over the string one character at a time
		for (unsigned i = 0; i < readIn.length(); i++) {
			argv[index][i] = readIn[i];
		}

		// Make argv[index] null terminating
		argv[index][readIn.length()] = '\0';

		// Increment index
		index++;
	}
	//Make argv null terminating
	argv[argc] = '\0';
}

/*
 * getCommand returns the name of the first argument given
 * or the name of the command
 */
char* CommandLine::getCommand() const {
	if (argv != NULL)		//Ensure that we have something to return
	{
		return argv[0];
	} else {
		return NULL;
	}
}

/*
 * getArgVector returns the ith argument passed into the command line
 */
char* CommandLine::getArgVector(int i) const {
	if (argv != NULL)		//Ensure that we have something to return
	{
		if (i > argc - 1) {
			return NULL;
		} else {
			return argv[i];
		}
	} else {
		return NULL;
	}
}

/*
 * getArgVector returns the entire arg vector minus an ampersand if it exists
 */
char** CommandLine::getArgVector() const {
	if (noAmpersand()) {
		return argv;
	} else {
		// If we have an ampersand, we don't want that being passed on to system calls, etc.
		char** copy = (char**)realloc(argv, argc);
		copy[argc-1] = '\0';
		return copy;
	}
}

/*
 *
 * noAmpersand returns true if the constructed command line contains no ampersand (at end of line)
 * otherwise, returns false;
 */
bool CommandLine::noAmpersand() const {
	// check last arg to see if it's an ampersand
	if (*argv[argc - 1] == '&') {
		return false;
	}
	return true;
}

/*
 * ~CommandLine deallocates the allocated memory in argv
 */
CommandLine::~CommandLine() {
	int index = 0;
	while (argv[index] != '\0') {
		free(argv[index]);
	}
	free(argv);
}

