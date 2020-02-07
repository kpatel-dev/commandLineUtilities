/*
 * 	Filename: mycat.cpp
 *  Created on: Oct. 3, 2019
 *  Author: kajalpatel
 *
 *  Description: Displays the contents of the files that are given as input arguements to the command on the terminal.
 */

#include <iostream>

using namespace std;
class Base{
            void jk(){
            cout<<"from base";
        }
    public:
        Base(std::string hi){
            cout<< hi<<endl;
        }

        

};
class Derived: public Base{
        void jk(){
            cout<<"from child";
        }
        

};

int f(int n, int v, int * p) {

*p = v;
v = v + 1;
return n+(*p);
}


int main() {
    Base b("hi");
    Derived a();

    b.jk();
    a.jk();
}



