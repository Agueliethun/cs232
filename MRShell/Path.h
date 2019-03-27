/*
 * Path.h
 *
 *  Created on: Feb 23, 2018
 *  Course: CS 232 at Calvin College
 *  Author: Royce Lloyd (ril2)
 *
 *  Path.h is the a class that defines a path to a directory and
 *  handles methods for the path
 */

#ifndef PATH_H_
#define PATH_H_

#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
using namespace std;



class Path {
public:
	Path();
	int find(const string& program) const;
	string getDirectory(int) const;

private:
	vector<string> fileNames;
};

#endif /* PATH_H_ */
