/*
 * 	Filename: mymv.cpp
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Moves and renames files according the the parameters passed in through the command line.
 */

#include <iostream>
#include "FileManager.h"

using namespace std;
int main(int argc, char *argv[]) {
	//read in the arguements passed in for the command
	char *oldName = argv[1];
	char *newName = argv[2];

	//create a FileManager for the file being operated on
	FileManager fileManager(oldName);

	//make sure the FileManager was correctly created
	if (fileManager.getErrorAsInt() != 0) {
		cout << "mv: " << fileManager.getErrorAsString() << endl;
	} else {
		//rename the file to the new name
		if (fileManager.renameFile(newName) != 0) {
			//if there is an error created because the files are on different systems, duplicate and then remove the old file instead
			if (fileManager.getErrorAsInt() == EXDEV) {
				//the copy paste is only required for regular files
				if (S_ISREG(fileManager.getType())) {

					//open a file stream to dump the file contents into, if the file doesn't exist, create it
					fstream dumpStream;
					dumpStream.open(newName, fstream::in | fstream::out | fstream::trunc);
					

					//dump the file to be copied into the stream to copy it
					if (fileManager.dump(dumpStream) == 0) {
						//remove the old file from the system
						if (fileManager.remove() != 0) {
							cout<< "mv: copied old file to new location, but could not remove old file : "
									<< fileManager.getErrorAsString() << endl;
						}
					} else {
						cout << "mv: failed to copy file to new location: "
								<< fileManager.getErrorAsInt() << endl;
					}
					//close the stream
					dumpStream.close();
				} else {
					//print any error message generated while trying to rename
					cout << "mv: (not a regular file) : "
							<< fileManager.getErrorAsString() << endl;
				}
			} else {
				//print any error message generated while trying to rename
				cout << "mv: cannot move " << oldName << " to " << newName
						<< " : " << fileManager.getErrorAsString() << endl;
			}
		}
	}

	return 0;
}
