/*
 * 	Filename: myrm.cpp
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: This removes the given files listed as parameters to the command.
 */

#include <iostream>
#include "FileManager.h"

using namespace std;
int main(int argc, char *argv[]) {
	//store the total number of arguements (files)
	int totalFiles = argc - 1;
	//create an array to hold dynamically allocated FileManager objects
	FileManager *fileManagers[totalFiles];

	//iterate through all the arguements passed in
	for (int i = 0; i < totalFiles; i++) {
		//dynamically create a new FileManager object for each file arguement
		fileManagers[i] = new FileManager(argv[i + 1]);
		//remove the file or display the error if it could not be removed
		if (fileManagers[i]->remove() != 0) {
			cout << "rm: cannot remove '" << fileManagers[i]->getName()
					<< "' : " << fileManagers[i]->getErrorAsString() << endl;
		}
	}

	//delete all the dynamically allocated FileManager objects
	for (int i = 0; i < totalFiles; i++) {
		delete fileManagers[i];
	}

	return 0;
}
