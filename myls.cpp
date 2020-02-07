/*
 * 	Filename: myls.cpp
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Lists the contents of directories and for other types of files, lists the file names.
 *  The files are passed in as parameters from the command line.
 *  This also implements the -l option to print the file in long format.
 *  If no file is specified, it will list the content of the current directory.
 */

#include <iostream>
#include <iomanip>
#include "FileManager.h"

using namespace std;


/**
 * function: splitName
 * parameters:
 * 		string &filePath : the full file path of the file
 * return:
 * 		the filename with the file path removed from the string
 *
 * description: this method splits the file path and returns just the name of the file
 */
string splitName(string &filePath) {
	size_t pos = filePath.find_last_of("/");
	return filePath.substr(pos + 1);
}


/**
 * function: getFileType
 * parameters:
 * 		mode_t fileType : the type of the file as a mode_t type
 * return:
 * 		the representation of the file type as a character
 *
 * description: this method converts the file type from mode_t type to a character
 */
char getFileType(mode_t fileType) {
	if (S_ISREG(fileType)) { //regular file
		return '-';
	} else if (S_ISCHR(fileType)) { //character special file
		return 'c';
	} else if (S_ISDIR(fileType)) { // directory
		return 'd';
	} else if (S_ISFIFO(fileType)) { // pipe or FIFO special file
		return 'p';
	} else if (S_ISLNK(fileType)) { //symbolic file
		return 'l';
	} else if (S_ISSOCK(fileType)) { //socket
		return 's';
	} else {
		return ' ';
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


/**
 * function: printLong
 * parameters:
 * 		FileManager &fileManager : the FileManager for the file that needs to be printed
 * return:
 * 		Returns nothing
 *
 * description: this method helps to print the info of the file for the ls -l option
 */
void printLong(FileManager &fileManager) {
	//get the name of the file and format it for printing with appropriate padding and the path removed
	string fileName = fileManager.getName();
	string formattedFileName; 
	try{
		formattedFileName = splitName(fileName).append(22 - fileName.length(), ' ');
	}catch(exception &e){
		//the length of the name was too long to format
		formattedFileName = splitName(fileName);
	}

	//get the size of the file and format it for printing with the appropriate padding
	string size = to_string(fileManager.getSize());
	string formattedSize = size.append(8 - size.length(), ' ');

	//print out all the info of the file
	cout << formattedFileName << " "
			<< getFileType(fileManager.getType())
			<< fileManager.getPermission() << " "
			<< fileManager.getOwner().name<< " "
			<< fileManager.getGroup().name << " "
			<< formattedSize << " "
			<< convertDate(fileManager.getModificationTime());
}

/**
 * function: printChildren
 * parameters:
 * 		FileManager &fileManager : the FileManager for the file that needs to be printed
 * 		bool isLongFormat : whether the format of the information should be long (include everything) or just the name
 * return:
 * 		Returns nothing
 *
 * description: this method helps to print the info or name of the children of a specific file (directory)
 */
void printChildren(FileManager &fileManager, bool isLongFormat) {
	//get the children vector of the file (directory)
	vector<FileManager> children = fileManager.getChildren();
	//create a string to hold the child name while iterating through the children vector
	string childName;

	//iterate through the child vector and print it according to the format it should be in
	for (unsigned int i = 0; i < children.size(); i++) {
		if (!isLongFormat) {
			//if its not long format, just print the name with the appropriate padding
			childName = children[i].getName();
			string fileName = (splitName(childName));
			try{
				fileName = fileName.append(22 - childName.length(), ' ');
			}catch(exception &e){
				//the length of the name was too long to format, just print it as it is
				;
			}
			cout << fileName;
			//after every 4 items printed, go to the next line for improved readability
			if ((i + 1) % 4 == 0 && i != 0) {
				cout << endl;
			}
		} else {
			//if the -l option is used, print the appropriate info
			printLong(children[i]);
		}
	}
	cout << endl;
}


int main(int argc, char *argv[]) {

	string firstArg;
	bool isLongFormat = false; //did the user ask for long format
	bool fileArguements = false; //did the user pass in filenames in the arguement

	//if there is more than one parameter passed in, check if it the long option should be used and how many files were passed in
	if (argc > 1) {
		string firstArg = argv[1];

		//check if the -l option is used
		isLongFormat = firstArg == "-l" ? true : false;

		//check if any file are passed in as arguements
		fileArguements =(isLongFormat && argc > 2) || (!isLongFormat && argc > 1) ? true : false;
	}

	//check if the file arguements are passed in
	if (fileArguements) {

		//determine the total number of files passed in
		int totalFiles = isLongFormat ? argc - 2 : argc - 1;

		//create an array to hold the dynamically allocated fileManager objects
		FileManager *fileManagers[totalFiles];

		//go through all the file arguements passed in
		for (int i = 0; i < totalFiles; i++) {

			//store the name of the file
			string fileName = isLongFormat ? argv[i + 2] : argv[i + 1];

			//dynamically create a new FileManager object for the given arguement
			fileManagers[i] = new FileManager(fileName.c_str());

			//check if the FileManager was succesfully created correctly
			if (fileManagers[i]->getErrorAsInt() == 0) {
				//if the file is a directory, all the children need to be printed
				if (S_ISDIR(fileManagers[i]->getType())) {
					cout << endl << fileName << ":" << endl;
					printChildren(*fileManagers[i], isLongFormat);
					cout << endl;
				} else {
					//if it is a regular file, only the name needs to be printed with the correct info depend if the -l option was used
					if (isLongFormat) {
						printLong(*fileManagers[i]);
					} else {
						cout << fileName << endl << endl;
					}
				}
			} else {
				cout << "ls: " << fileName << " : "<< fileManagers[i]->getErrorAsString() << endl;
			}

		}

		//delete all the dynamically allocated FileManager objects
		for (int i = 0; i < totalFiles; i++) {
			delete fileManagers[i];
		}

	} else {
		//display all the contents in the current directory if there are no file arguements
		FileManager fileManager(".");
		if (fileManager.getErrorAsInt() == 0) {
			printChildren(fileManager, isLongFormat);
		} else {
			cout << "ls : " << fileManager.getErrorAsString() << endl;
		}
	}

	return 0;
}
