/*
 * 	Filename: FileManager.h
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Declares the member methods and member variables required to implemented the FileManager class.
 *  Each instance of the class will hold information about one specific file from the file system.
 *  This class also provides methods to perform operations on the files such as remove, copy, move, rename and compare.
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <string>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstring>
#include "User.h"

class FileManager {
private:
	std::string name; // the file name which includes the full path to the current directory
	mode_t type; // the type of the file as a string
	off_t size; // the size of the file in bytes
	User<uid_t> owner; // the user owner of the file
	User<gid_t> group; 	// the user group of the file
	std::string permission;	// the permission of the file
	time_t accessTime; 	// the time of last access
	time_t modificationTime; 	// the time of the last modification
	time_t statusChangeTime; 	// the time of the last status change
	blksize_t blockSize; // block size of file to determine optimal chunk for I/O operations
	std::vector<FileManager> children; // if its a directory type, it should store the collection of objects under it (the children)
	int error; // cache the error value of the most recent operation executed (should be 0 for successful operations)

	//helper methods for initialization of the object - private because does not need to be used outside the object
	void initializePermission(mode_t &st_mode);

public:
	//constructor
	FileManager();
	FileManager(const char *fileName);

	//destructor
	~FileManager(); //probably need to delete the dynamically stored vector

	//getters
	std::string getName();
	mode_t getType();
	off_t getSize();
	User<uid_t> getOwner();
	User<gid_t> getGroup();
	std::string getPermission();
	time_t getAccessTime();
	time_t getModificationTime();
	time_t getStatusChangeTime();
	blksize_t getBlockSize();
	std::vector<FileManager> getChildren();
	int getErrorAsInt();
	std::string getErrorAsString();

	//setter
	int setFileName(const char *newName);

	//other functions
	int expand();
	int renameFile(const char *newName);
	int dump(std::fstream &fileStream);
	int remove();
	int compare(FileManager &otherFile);

};

#endif /* FILEMANAGER_H_ */
