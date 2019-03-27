/*
 * Prompt.cpp
 *
 *  Created on: Feb 23, 2018
 *  Course: CS 232 at Calvin College
 *  Author: Royce Lloyd (ril2)
 *
 *  Prompt.cpp is a class that constructs a prompt for the user
 */

#include "Prompt.h"

//Construct the prompt
Prompt::Prompt() {

	//create a string for the first 365 characters in the current working directory
	char temp[365];
	string cwd = getcwd(temp, 365);

	//Check for errors
	if (getcwd == NULL)
	{
		string errorMsg;
		perror(errorMsg.c_str());
		cerr << "Prompt(): Error making prompt. " << errorMsg << endl;
	} else {
		valuePrompt = cwd;
	}
}
