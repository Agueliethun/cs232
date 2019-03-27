#!/bin/bash
LANG=C

# this function removes all spaces from the text passed in
removespaces() {
    echo "$1" | sed -e "s/ //g"
}

# this function removes the dash, numbers, and .zip text from the zip file
# so we can make a good directory name
createdirectory() {
    echo "$1"  | sed -e "s/ //g" | sed -e 's/-[0123456789]\+.zip//g'
}

# this function returns the proper directory names
# i.e. it removes the extra numbers and junk from the end of filenames
removeextratext() {
	echo "$1"| sed -e "s/ //g" | sed -e "s/_[0123456789]\+_.*_.*_//g"
}

# this function removes the directory, leaving just a filename
# e.g. C:/Matthew/File will turn into just File
getendofdirectory() {
	echo "$1" | sed -e "s/.*\///g"
}

# this function recursively fixes the folder and 
#filenames in the main directory given as $1
fixnames() {
	# loop through all files in the directory given
	for filename in "$1"/* ; do
		# if the type of file is a directory
		if [[ -d "$filename" ]] ; then

			if [[ "$verbose_mode" == TRUE ]] ; then
				echo "Current directory is: $filename" >&2
			fi

			# create a better filename to store things in
			fixedname=$(removeextratext "$filename")

			if [[ "$verbose_mode" == TRUE ]] ; then
				echo "New directory is: $fixedname" >&2
			fi

			# make the new directory with the proper name
			mkdir -p "$fixedname"
			
			# check for errors and print output
			if [[ $? == 0 ]] ; then
				if [[ "$verbose_mode" == TRUE ]] ; then
					echo "New directory created successfully" >&2
				fi
			else
				echo "Directory could not be created" >&2
				exit
			fi

			if [[ "$verbose_mode" == TRUE ]] ; then
				echo "Fixing files inside this directory" >&2
			fi

			# recursively fix the subfiles and remove the old directory
			$(fixnames "$filename" "$fixedname")
			rmdir "$filename"

			# check for errors and print output
			if [[ $? == 0 ]] ; then
				if [[ "$verbose_mode" == TRUE ]] ; then
					echo -e "Old directory removed\n" >&2
				fi
			else
				echo "Directory could not be removed" >&2
				exit
			fi
		# if the file is just a file
		elif [[ -f "$filename" ]] ; then

			if [[ "$verbose_mode" == TRUE ]] ; then
				echo "Current file is: $filename" >&2
			fi

			# remove spaces and the directory info
			fixedfilename=$(removespaces "$filename")
			fixedfilename=$(getendofdirectory "$fixedfilename")
			
			# if there is a second argument, it means we are running with a given directory. 
			# If so, put it there. Otherwise, just move it to the new file name
			if [[ "$2" ]] ; then
				mv "$filename" "$2/$fixedfilename"
			else
				mv "$filename" "$fixedfilename"
			fi
		# if the file is a zip, just unzip it
		elif [[ "$filename" =~ \.zip ]] ; then
			unzip "$filename"
		fi
	done
}

# grab our arguments
inputfile="$@"

# check if we are running verbose mode
if [[ "$1" == "--verbose" || "$1" == "-v" ]] ; then
	verbose_mode=TRUE
	shift
else
	verbose_mode=FALSE
fi

# get an appropriate name for our new directory
directory=$(createdirectory "$1")

if [[ "$verbose_mode" == TRUE ]] ; then
	echo "New directory is: $directory"
fi

# check to make sure a directory by that name doesn't already exist
if [[ -d "$directory" ]] ; then
	echo "Cannot unzip: directory exists already, please delete directory to continue"
	exit
fi

# make the directory
mkdir -p "$directory"

# check for errors, and output
if [[ $? == 0 ]] ; then
	if [[ "$verbose_mode" == TRUE ]] ; then
		echo "New directory created successfully"
	fi
else
	echo "Directory could not be created"
	exit
fi

# call the unzip function, routing the output to /dev/null so we don't see it
unzip "$1" -d "$directory" > /dev/null

# fix the names of the unzipped files
echo -e $(fixnames "$directory")
