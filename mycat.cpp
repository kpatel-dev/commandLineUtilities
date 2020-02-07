/*
 * 	Filename: mycat.cpp
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Displays the contents of the files that are given as input arguements to the command on the terminal.
 */

#include <iostream>
#include "FileManager.h"

using namespace std;

int main(int argc, char *argv[]) {
	//check how many files were inputted as parameters
	int totalFiles = argc - 1;

	//create a temporary (dummy file) for the filestream to read from the files
	string tempFile = "temp.txt";

	//create an array to dynamically allocate FileManager objects for all the files inputted as arguements
	FileManager *fileManagers[totalFiles];

	//iterate through the files, creating a FileManger object for each of them and dump the contents onto the termial
	for (int i = 0; i < totalFiles; i++) {

		fileManagers[i] = new FileManager(argv[i + 1]);

		//make sure a valid file manager was object before attempting to perform the operation,
		//skip the object if it is not a valid file or the object could not be created properly for it
		if (fileManagers[i]->getErrorAsInt() != 0) {
			cout << "cat: " << fileManagers[i]->getName() << " : "
					<< fileManagers[i]->getErrorAsString() << endl;
			continue;
		}

		//create a stream for the cat operation to be passed into the dump method to read the files
		fstream catStream;
		catStream.open(tempFile,fstream::in | fstream::out | fstream::trunc);

		//make sure the stream is clear before starting
		catStream.clear();

		//dump the content of the file into the cat stream
		if (fileManagers[i]->dump(catStream) != 0) {
			//make sure the dump was successful, if not, show the error
			cout << "cat: " << fileManagers[i]->getName() << " : "
					<< fileManagers[i]->getErrorAsString() << endl;
		} else {
			//reset the file pointed to the beginning of the catStream and display the contents of the file to the terminal
			catStream.seekg(0, catStream.beg);
			cout << catStream.rdbuf();
			catStream.close();
			catStream.clear();
		}

		//create a filemanager for the temp file to delete it from the filesystem
		FileManager tempFileManager(tempFile.c_str());
		tempFileManager.remove();

	}

	//delete all the dynamically allocated FileManager objects
	for (int i = 0; i < totalFiles; i++) {
		delete fileManagers[i];
	}

	return 0;
}
