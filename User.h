 /*
 * 	Filename: User.h
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Holds the information about users and groups of the file system. This is a templated file,
 *   the id should be stored according to the type of user the struct is defining.
 */

#ifndef USER_H_
#define USER_H_

#include <string>

//Type is for the type the id is stored as for the user
template<typename Type>
struct User {
	public:
		//the id of the user
		Type id;
		//the name of the user
		std::string name;
};

#endif /* USER_H_ */
