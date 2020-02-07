/*
 * 	Filename: mycp.cpp
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Copies a file from the source to the destination which are provided as parameters from the command line.
 */

#include <iostream>
#include "FileManager.h"

using namespace std;

int main(int argc, char *argv[]) {
	//read the files passed in as parameters to the copy operation
	char *file1 = argv[1];
	char *file2 = argv[2];

	//create a filemanager for the file being copied
	FileManager fileManager(file1);

	//make sure the file exists and were able to create a filemanager object correctly for it
	if (fileManager.getErrorAsInt() != 0) {
		cout << "cp: " << fileManager.getErrorAsString() << endl;
	} else {
		//open the second parameter as a file stream
		fstream dumpStream;
		dumpStream.open(file2, fstream::in | fstream::out | fstream::trunc);


		//make sure the stream is clear
		dumpStream.clear();

		//use the dump method to read file1 into file2 using the file stream (dumpStream)
		if (fileManager.dump(dumpStream) != 0) {
			//if the opration was not successful, output the error to the terminal
			cout << "cp: failed to copy file to new location: "
					<< fileManager.getErrorAsString() << endl;
		}

		//close the stream
		dumpStream.close();
	}

	return 0;
}
