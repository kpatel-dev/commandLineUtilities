/*
 * 	Filename: FileManager.cpp
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Defines the member methods required to implemented the FileManager class as defined in FileManage.h.
 *  Each instance of the class will hold information about one specific file from the file system.
 *  This class also provides methods to perform operations on the files such as remove, copy, move, rename and compare.
 */

#include <iostream>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <unistd.h>
#include "FileManager.h"

using namespace std;

/**
 * function: initalizePermission
 * parameters:
 * 		mode_t &st_mod : the permission retrieved from the stat system call as a mode_t type
 * return:
 * 		nothing returned
 *
 * description: helper method to convert the st_mode from mode_t to a string and initialize the permission variable
 */
void FileManager::initializePermission(mode_t &st_mode) {
	//store the permission in rwx format
	this->permission.append((st_mode & S_IRUSR) ? "r" : "-");
	this->permission.append((st_mode & S_IWUSR) ? "w" : "-");
	this->permission.append((st_mode & S_IXUSR) ? "x" : "-");
	this->permission.append((st_mode & S_IRGRP) ? "r" : "-");
	this->permission.append((st_mode & S_IWGRP) ? "w" : "-");
	this->permission.append((st_mode & S_IXGRP) ? "x" : "-");
	this->permission.append((st_mode & S_IROTH) ? "r" : "-");
	this->permission.append((st_mode & S_IWOTH) ? "w" : "-");
	this->permission.append((st_mode & S_IXOTH) ? "x" : "-");
}

/**
 * function: FileManager
 * parameters:
 * 		No parameters
 * return:
 * 		The FileManager object that is created and initialized
 *
 * description: default constructor to create a FileManager object
 */
FileManager::FileManager() {
		this->error = 0;
		//initialize all the variables to -1 or empty string accordingly
		this->name = "";
		this->type = -1;
		this->size = -1;
		this->owner.id = -1;
		this->owner.name = "";
		this->group.id = -1;
		this->group.name = "";
		this->permission = "";
		this->accessTime = -1;
		this->modificationTime = -1;
		this->statusChangeTime = -1;
		this->blockSize = -1;
}

/**
 * function: FileManager
 * parameters:
 * 		const char *fileName : the name of the file on the system
 * return:
 * 		The FileManager object that is created and initialized
 *
 * description: constructor for created a FileManager object for a file on the file system.
 */
FileManager::FileManager(const char *fileName) {
	struct stat statbuf;
	int statStatus = stat(fileName, &statbuf);

	//check if the the stat call worked on the filename provided
	if (statStatus == 0) {
		//extract all the info from the stat call and store it in the FileManager object
		this->name = fileName;
		this->type = statbuf.st_mode;
		this->size = statbuf.st_size;
		this->owner.id = statbuf.st_uid;
		this->owner.name = getpwuid(owner.id)->pw_name;
		this->group.id = statbuf.st_gid;
		this->group.name = getgrgid(group.id)->gr_name;
		this->initializePermission(statbuf.st_mode);
		this->accessTime = statbuf.st_atime;
		this->modificationTime = statbuf.st_mtime;
		this->statusChangeTime = statbuf.st_ctime;
		this->blockSize = statbuf.st_blksize;

		//initialize the internal error code to be 0
		this->error = 0;
	} else {
		//if the stat function was not successful, store the error
		this->error = errno;
		this->name = fileName;

		//initialize all the variables to -1 or empty string accordingly
		this->type = -1;
		this->size = -1;
		this->owner.id = -1;
		this->owner.name = "";
		this->group.id = -1;
		this->group.name = "";
		this->permission = "";
		this->accessTime = -1;
		this->modificationTime = -1;
		this->statusChangeTime = -1;
		this->blockSize = -1;
	}
}

/**
 * function: ~FileManager
 * parameters:
 * 		No parameters
 * return:
 *		Nothing returned
 *
 * description: This is the destructor for the FileManager object.
 * Since none of the member variables were dynamically allocated, there is nothing to be implemented.
 */
FileManager::~FileManager() {
	;
}

/**
 * function: getName
 * parameters:
 * 		No parameters
 * return:
 *		The name of the file is returned as a string.
 *
 * description: Return the file name stored in the FileManager object
 */
std::string FileManager::getName() {
	return this->name;
}

/**
 * function: getType
 * parameters:
 * 		No parameters
 * return:
 *		Returns the type of the file as a mode_t type
 *
 * description: Return the type of the file stored in the FileManager object
 */
mode_t FileManager::getType() {
	return this->type;
}

/**
 * function: getSize
 * parameters:
 * 		No parameters
 * return:
 * 		Return the size of the file as a off_t type
 *
 * description: Returns the size of the file stored in the FileManager object
 */
off_t FileManager::getSize() {
	return this->size;
}

/**
 * function: getOwner
 * parameters:
 * 		No parameters
 * return:
 * 		Return the owner of the file as a User struct
 *
 * description: Returns the owner of the file stored in the FileManager object
 */
User<uid_t> FileManager::getOwner() {
	return this->owner;
}

/**
 * function: getGroup
 * parameters:
 * 		No parameters
 * return:
 * 		Returns the group of the file as a User struct
 *
 * description: Returns the group of the file stored in the FileManager object
 */
User<gid_t> FileManager::getGroup() {
	return this->group;
}

/**
 * function: getPermission
 * parameters:
 * 		No parameters
 * return:
 * 		Returns the permission of the file as a string
 *
 * description: Returns the permission of the file stored in the FileManager object
 */
std::string FileManager::getPermission() {
	return this->permission;
}

/**
 * function: getAccessTime
 * parameters:
 * 		No parameters
 * return:
 * 		Returns the access time of file as a time_t type
 *
 * description: Returns the access time of the files stored in the FileManager object
 */
time_t FileManager::getAccessTime() {
	return this->accessTime;
}

/**
 * function: getModificationTime
 * parameters:
 * 		No parameters
 * return:
 * 		Returns the modification time of the  file as a time_t type
 *
 * description: Returns the modification time of the file stored in the FileManager object
 */
time_t FileManager::getModificationTime() {
	return this->modificationTime;
}

/**
 * function: getStatusChangeTime
 * parameters:
 * 		No parameters
 * return:
 * 		Returns the status change time of the file as a time_t type
 *
 * description:	Returns the status change time of the file stored in the FileManager object
 */
time_t FileManager::getStatusChangeTime() {
	return this->statusChangeTime;
}

/**
 * function: getBlockSize
 * parameters:
 * 		No parameters
 * return:
 * 		Returns the ideal I/O blocksize of the file as a blksize_t of the file
 *
 * description: Returns the ideal I/O blocksize of the file stored in the FileManager object
 */
blksize_t FileManager::getBlockSize() {
	return this->blockSize;
}

/**
 * function: getChildren
 * parameters:
 * 		No parameters
 * return:
 * 		Returns the children file as FileManager vector
 *
 * description: Returns the children vector stored in the FileManager object
 */
std::vector<FileManager> FileManager::getChildren() {
	expand();
	return this->children;
}

/**
 * function: getErrorAsint
 * parameters:
 * 		No parameters
 * return:
 * 		Returns the internal error of the last process run on the object as an int
 *
 * description: Returns the internal error stored on the FileManager object
 */
int FileManager::getErrorAsInt() {
	return this->error;
}

/**
 * function: getErrorAsString
 parameters:
 * 		No parameters
 * return:
 * 		Returns the internal error of the last process run on the object as a String
 *
 * description: Returns the internal error stored on the FileManager object
 */
string FileManager::getErrorAsString() {
	string errorString = strerror(this->error);
	return errorString;
}

/**
 * function: setFileName
 * parameters:
 * 		const char *newName : the new name of the file
 * return:
 * 		The internal error set by the rename operation done on the file
 *
 * description: Renames the file name attribute and the actual file name on the file system
 */
int FileManager::setFileName(const char *newName) {
	return renameFile(newName);
}

/**
 * function: expand
 * parameters:
 * 	No parameters
 * return:
 *		The internal error set by the expand operation done on the file
 *
 * description: Populates the children vector in the FileObject if it is a directory
 */
int FileManager::expand() {
	//make sure the file is a directory
	if (S_ISDIR(this->type)) {
		//clear out whatever is currently in the children vector
		this->children.clear();

		//open the directory and iterate through its objects
		DIR *dir;
		struct dirent *ent;
		string currentFile;
		if ((dir = opendir((this->name).c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				currentFile = ent->d_name;

				//create a file manager for all the files/directories inside the directory
				//ignore the current folder and the root folder (only need children)
				if (currentFile != "." && currentFile != "..") {
					FileManager filemanager((this->name + "/" + currentFile).c_str());
					this->children.push_back(filemanager);
				}
			}
			closedir(dir);
		}
		this->error = errno;
	} else {
		//if the file is not a directory, set the error as operation not supported
		this->error = ENOTSUP;
	}
	return this->error;
}

/**
 * function: renameFile
 * parameters:
 * 		const char *newName : the new name of the file
 * return:
 * 		The internal error set by the rename operation done on the file
 *
 * description: Renames the file name attribute and the actual file name on the file system
 */
int FileManager::renameFile(const char *newName) {
	if (rename((this->name).c_str(), newName) == 0) {
		this->name = newName; //update the filename attribute
	}
	this->error = errno;
	return this->error;
}

/**
 * function: dump
 * parameters:
 * 		fstream &dumpStream : the file stream to dump the content of the file to
 * return:
 * 		The internal error set by the dump operation done on the file
 *
 * description: Reads the contents of the file in the ideal I/O blocksize and dumps it into the filestream provided.
 * The operation is only done on regular files.
 */
int FileManager::dump(fstream &dumpStream) {
	//make sure that this is a regular file
	if (S_ISREG(this->type)) {
		//open a input filestream for reading the file
		ifstream inputStream;
		inputStream.open(this->name);

		//if the stream for the file does not open, return the error code
		if (!inputStream.is_open()) {
			this->error = errno;
			return this->error;
		}

		//create a buffer of the ideal I/O blocksize for reading the file
		int buffSize = this->blockSize;
		char *buffer = new char[buffSize];

		//keep reading the file till the end of the file is reached
		while (!inputStream.eof()) {
			inputStream.read(buffer, buffSize);
			//only write to the dumpStream the amount of bytes that were actually read from the file
			dumpStream.write(buffer, inputStream.gcount());
		}

		//close the stream and delete the dynmaically allocated buffer.
		inputStream.close();
		delete[] buffer;
		this->error = errno;
	} else {
		//this method is not supported for files that are not regular files
		this->error = ENOTSUP;
	}

	return this->error;

}

/**
 * function: remove
 * parameters:
 * 		No parameters
 * return:
 *		Return the internal error set by the remove operation on the FileObject
 *
 * description: Remove the file from the filesystem and reset all the parameters of FileManager object
 */
int FileManager::remove() {
	//remove the file using the unlink method
	if (unlink(this->name.c_str()) == 0) {
		//if the removal was successul, reset the values
		//initialize all the variables to -1 or empty string accordingly
		this->type = -1;
		this->size = -1;
		this->owner.id = -1;
		this->owner.name = "";
		this->group.id = -1;
		this->group.name = "";
		this->permission = "";
		this->accessTime = -1;
		this->modificationTime = -1;
		this->statusChangeTime = -1;
		this->blockSize = -1;
	}
	this->error = errno;
	return this->error;
}

/**
 * function: compare
 * parameters:
 * 		FileManager &otherFile : the file FileManager object to be compared to
 * return:
 * 		Returns 0 if the files are the same
 * 		Returns -1 if the files are different
 * 		Returns the internal error set by the compare operation if it was not successful
 *
 * description: Compares the contents of the file to the file sent in as a parameter.
 * Each file is read using the ideal I/O block size of this FileManager object.
 * This operation is only supported if both files are regular files.
 */
int FileManager::compare(FileManager &otherFile) {
	//make sure both of these files are regular files
	if (!S_ISREG(this->type) || !S_ISREG(otherFile.getType())) {
		this->error = ENOTSUP;
		return this->error;
	}

	//if the two files are not the same size, they cannot be the same
	if (this->size != otherFile.getSize()) {
		return -1; //not the same
	}

	//open an input file stream to read from each file
	ifstream file1IStream(this->name);
	ifstream file2IStream(otherFile.getName());

	//create a buffer of the ideal I/O block size for the file reading
	int bufferSize = this->blockSize;
	char *buffer1 = new char[bufferSize];
	char *buffer2 = new char[bufferSize];

	//make sure both file streams were able to open
	if (!file1IStream.is_open() || !file2IStream.is_open()) {
		this->error = errno;
		return this->error;
	}

	//keep reading the file until the ends of the streams are reached
	while (file1IStream.eof() || file2IStream.eof()) {
		file1IStream.read(buffer1, bufferSize);
		file2IStream.read(buffer2, bufferSize);
		if (memcmp(buffer1, buffer2, bufferSize) != 0) {
			return -1; //if the buffers do not hold the same value, return false (-1)
		}
	}

	delete[] buffer1;
	delete[] buffer2;

	//at this point if there was no error set, the error should be 0 and this means the
	//comparison was successful and the files are the same.
	this->error = errno;
	return this->error;

}

