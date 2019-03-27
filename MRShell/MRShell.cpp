/*
 * MRShell.cpp
 *
 *  Created on: Feb 23, 2018
 *  Course: CS 232 at Calvin College
 *  Authors: Matthew Nykamp (mrn6) and Royce LLoyd (ril2)
 *
 *  MRShell.cpp contains the core code to run a shell. It is capable of running three built-in methods:
 *  cd, pwd, and exit. It is also capable of running any system programs stored in path.
 */

#include "MRShell.h"

/*
 * Constructor gives a welcome message for friendliness,
 * and also initializes a path and prompt for the shell
 */
MRShell::MRShell() {
	prompt = new Prompt();
	path = new Path();
	cout << "MR. Shell bids you welcome to this fine executing environment!" << endl;
}

/*
 * changeDirectory is an internal method which controls the behavior of the "cd" command
 *
 */
void MRShell::changeDirectory(CommandLine* cm) {
	// We only need one argument
	char* arg = cm->getArgVector(1);
	int ret;

	if (arg != NULL) {
		ret = chdir(arg);
	} else {
		// Return to default directory
		ret = chdir("/");
	}
	if (ret == 0) {
		prompt = new Prompt();
	} else {
		cout << "Invalid path for command cd." << endl;
	}
}

/*
 * systemProgram is an internal method which controls the behavior of calling system programs
 */
void MRShell::systemProgram(bool shouldWait, CommandLine* cm) {
	// Store a reference to the existing environment
	extern char** environ;

	// Store the command and path for that command
	string command = cm->getCommand();
	int whichPath = path->find(command);


	if (whichPath != -1) {
		// Fork a child
		pid_t pid = fork();

		// If this is the child process then execve the system program
		if (pid == 0) {
			string fullPath = path->getDirectory(whichPath) + "/"
					+ cm->getCommand();
			execve(fullPath.c_str(), cm->getArgVector(), environ);
			exit(-1);
		}
		// If this is the parent, wait if an ampersand was given. Otherwise
		// just go on
		else if (pid > 0) {
			if (shouldWait) {
				int* status = NULL;
				waitpid(pid, status, 0);
			}
		} else {
			cout << "Cannot fork a new process." << endl;
		}
	} else {
		cout << "Cannot find a system program or built in function with name: "
				<< command << ". Please enter a new input." << endl;
	}
}

/*
 * run is the main method for MRShell. It handles command line
 * inputs and executes built-in functions and system programs
 */
void MRShell::run() {
	bool shouldExit = false;
	string input = "";

	// The main loop
	while (!shouldExit) {
		// Print out the current directory and name of shell
		cout << "MRShell: ~" << prompt->get() << "$ " << flush;

		// Get a new command line
		getline(cin, input);
		istringstream inputstream(input);
		CommandLine *cm = new CommandLine(inputstream);
		string command = cm->getCommand();

		// See if there's an ampersand
		bool shouldWait = cm->noAmpersand();

		// Check which command is being run
		if (command == "cd") {
			changeDirectory(cm);
		} else if (command == "pwd") {
			cout << prompt->get() << endl;
		} else if (command == "exit") {
			shouldExit = true;
		} else {
			systemProgram(shouldWait, cm);
		}
	}

	cout << "Mr. Shell bids you farewell~" << endl;

}
