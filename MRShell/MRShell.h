/*
 * MRShell.h
 *
 *  Created on: Feb 23, 2018
 *  Course: CS 232 at Calvin College
 *  Authors: Matthew Nykamp (mrn6) and Royce LLoyd (ril2)
 *
 *  MRShell.h contains the core code to run a shell. It is capable of running three built-in methods:
 *  cd, pwd, and exit. It is also capable of running any system programs stored in path.
 */

#ifndef MRSHELL_H_
#define MRSHELL_H_
#include "Path.h"
#include "Prompt.h"
#include "CommandLine.h"
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <sys/wait.h>
using namespace std;

class MRShell {
public:
	MRShell();
	void run();

private:
	Path *path;
	Prompt *prompt;
	void changeDirectory(CommandLine* cm);
	void systemProgram(bool shouldWait, CommandLine* cm);
};

#endif /* MRSHELL_H_ */
