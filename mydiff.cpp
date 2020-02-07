/*
 * 	Filename: mydiff.cpp
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Compares two files that are passed in as parameters through the command line.
 *  It will only report if they are different or the same.
 */

#include <iostream>
#include "FileManager.h"

using namespace std;
int main(int argc, char *argv[]) {
	//read in the files passed in as arguements and create file manager objects for them
	char *file1 = argv[1];
	char *file2 = argv[2];
	FileManager fileManager1(file1);
	FileManager fileManager2(file2);

	//make sure the files opened and the objects were created correctly
	if (fileManager1.getErrorAsInt() != 0) {
		cout << "diff : " << fileManager1.getName() << " had an issue:"
				<< fileManager1.getErrorAsString() << endl;
	} else if (fileManager2.getErrorAsInt() != 0) {
		cout << "diff : " << fileManager2.getName() << " had an issue: "
				<< fileManager2.getErrorAsString() << endl;
	} else {
		//compare the two files
		if (fileManager1.compare(fileManager2) != 0) {
			//check if an error was generated
			if (fileManager1.getErrorAsInt() == 0) {
				//if not error was generated and the method didnt return 0, the files are different
				cout<< "diff : DIFFERENT - the contents of the file are different"<< endl;
			} else {
				cout << "diff : " << fileManager1.getErrorAsString() << endl;
			}
		} else {
			//if 0 was returned the files are the same and the comparison was successful
			cout << "diff : SAME - the contents of the file are the same"<< endl;
		}

	}

	return 0;
}
