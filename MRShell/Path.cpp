/*
 * Path.cpp
 *
 *  Created on: Feb 23, 2018
 *  Course: CS 232 at Calvin College
 *  Author: Royce Lloyd (ril2)
 *
 *  Path.cpp is the a class that defines a path to a directory and
 *  handles methods for the path
 */

#include "Path.h"

//Constructor establishes a path to a directory
Path::Path() {
	char* path;

	//Use the environment variable PATH and make sure it's not NULL
	path = getenv("PATH");
	if (path == NULL) {
		string errorMsg;
		perror(errorMsg.c_str());
		cerr << "Path cannot be established: " << errorMsg << endl;
	}

	istringstream iss(path);

	//Enter the file names into a the vector of strings
	while (!iss.eof()) {
		string fileName;
		getline(iss, fileName, ':');

		fileNames.push_back(fileName);
	}
}

//Find a program in a directory
int Path::find(const string& program) const {

	//Loop through the file names and open the direcotry at each given location
	for (unsigned i = 0; i < fileNames.size(); i++) {
		DIR *directory = NULL;
		directory = opendir(fileNames[i].c_str());

		//Handle the NULL case, if a path cannot be established
		if (directory == NULL) {
			string errorMsg;
			perror(errorMsg.c_str());
			cerr << "Cannot open a PATH directory to " << fileNames[i] << ": "
					<< errorMsg << endl;
			return -1;
		} else {
			//Point to the items in the directory
			struct dirent *info = readdir(directory);

			//Loop through to find the program
			while (info != NULL)
			{
				if (strcmp(info->d_name, program.c_str()) == 0)
				{
					return i;
				}
				info = readdir(directory);
			}

			//Close the directory to ensure safe code
			if (closedir(directory) == -1) {
				string errorMsg;
				perror(errorMsg.c_str());
				cerr << "Cannot close directory: " << errorMsg << endl;
			}
		}
	}

	return -1;
}

//Return method to return the i-th directory
string Path::getDirectory(int i) const {
	if (i >= fileNames.size() || i < 0) {
		cerr << "getDirectory(): index out of bounds error" << endl;
		return NULL;
	}
	return fileNames[i];
}
