/*
 * Prompt.h
 *
 *  Created on: Feb 23, 2018
 *  Course: CS 232 at Calvin College
 *  Author: Royce Lloyd (ril2)
 *
 *  Prompt.h is a class that constructs a prompt for the user
 */

#ifndef PROMPT_H_
#define PROMPT_H_

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

class Prompt {
public:
	Prompt();
	string get() const {return valuePrompt;};
private:
	string valuePrompt;
};

#endif /* PROMPT_H_ */
