// Created by Matthew Nykamp on 2-12-18
// For CS 232

// Homework 2
// This file provides a function which safely copies
// the contents of a source file to a destination file


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// The usage of stat was taken from:
// https://stackoverflow.com/questions/11276521/determine-file-type-in-c
#include <sys/stat.h>

int main( int argc, char * argv[] )
// The knowledge of how command line arguments work came from:
// https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm
{
	// Make sure we have the correct number of arguments
	if ( argc != 3)
	{
		// Otherwise print an error message
		fprintf(stderr, "Wrong number of arguments!\nCorrect format: copy <src> <dest>\n");
		return -1;
	}
	else
	{
		// Create a string with the first argument in it
		char * src = argv[1];

		// Knowledge of files was somewhat found at:
		// https://stackoverflow.com/questions/5672746/what-exactly-is-the-file-keyword-in-c
		// We can use just r, since we won't need to write or append
		FILE* srcfile = fopen(src, "r");

		// Check to see if the file opened correctly
		if (srcfile == NULL)
		{
			perror("Error opening source file");
			return -1;
		}

		// The following code is based off of:
		// https://stackoverflow.com/questions/40163270/what-is-s-isreg-and-what-does-it-do
		struct stat fileinfo;
		stat(src, &fileinfo);
		if (!S_ISREG(fileinfo.st_mode))
		{
			fprintf(stderr, "This file is not a regular type. Please choose a different file.\n");
			return -1;
		}

		// Create a string with the second argument in it
		char * dest = argv[2];

		// Check to make sure the file doesn't exist, code inspired by:
		// https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
		if (access(dest, F_OK ) != -1)
		{
			fprintf(stderr, "The destination file already exists. Please choose a different name.\n");
			return -1;
		}

		// Open a new file with the name that we were given
		FILE * destfile = fopen(dest, "w");

		// Create a character to act as a buffer between the two files
		char next = fgetc(srcfile);

		// As long as the next character we grab isn't EOF
		while (  next != EOF )
		{
			fputc(next, destfile);
			next = fgetc(srcfile);
		}

		fclose(srcfile);
		fclose(destfile);

	}

	exit(0);
}