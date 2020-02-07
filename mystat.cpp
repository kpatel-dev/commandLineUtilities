/*
 * 	Filename: mystat.cpp
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Outputs all the information on the file inputed as a parameter to the command.
 */

#include <iostream>
#include "FileManager.h"

using namespace std;

/**
 * function: getFileType
 * parameters:
 * 		mode_t fileType : the type of the file as a mode_t type
 * return:
 * 		the representation of the file type as a string
 *
 * description: this method converts the file type from mode_t type to a string
 */
string getFileType(mode_t fileType) {
	if (S_ISREG(fileType)) { //regular file
		return "regular";
	} else if (S_ISCHR(fileType)) { //character special file
		return "character special";
	} else if (S_ISDIR(fileType)) { // directory
		return "directory";
	} else if (S_ISFIFO(fileType)) { // pipe or FIFO special file
		return "pipe/FIFO";
	} else if (S_ISLNK(fileType)) { //symbolic file
		return "symoblic";
	} else if (S_ISSOCK(fileType)) { //socket
		return "socket";
	} else {
		return " ";
	}
}

/**
 * function: convertDate
 * parameters:
 * 		time_t time : the time as time_t type
 * return:
 * 		the time converted to a human readable string
 *
 * description: this method converts the time from unix timestamp to human readable time string
 */
string convertDate(time_t time) {
	return asctime(localtime(&time));
}

int main(int argc, char *argv[]) {
	//read the file name from the parameter passed in and create the FileManager object for it
	char *fileName = argv[1];
	FileManager fileManager(fileName);

	//print the file info from the stat or print the error message if the the stat call failed
	if (fileManager.getErrorAsInt() != 0) {
		cout << "stat: could not stat '" << fileManager.getName() << "' : "
				<< fileManager.getErrorAsString() << endl;
	} else {
		//print information about the file, its type, its ideal I/O blocksize and its size
		cout << "File: " << fileManager.getName() << endl;
		cout << "File Type: " << getFileType(fileManager.getType()) << endl;
		cout << "Size: " << fileManager.getSize() << endl;
		cout << "IO Block Size: " << fileManager.getBlockSize() << endl;

		//print the owner and group the file belongs to
		cout << "Owner: (id= " << fileManager.getOwner().id << "/  name= "
				<< fileManager.getOwner().name << ")" << endl;
		cout << "Group: (id= " << fileManager.getGroup().id << "/  name= "
				<< fileManager.getGroup().name << ")" << endl;

		//print the permission info
		cout << "Permissions: " << fileManager.getPermission() << endl;

		//correctly format and print the required times
		cout << "Access: " << convertDate(fileManager.getAccessTime()) << endl;
		cout << "Modify:  " << convertDate(fileManager.getModificationTime())<< endl;
		cout << "Status: " << convertDate(fileManager.getStatusChangeTime())<< endl;

	}

	return 0;
}
