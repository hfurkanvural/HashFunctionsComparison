#ifndef HashNode_h
#define HashNode_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;


class HashNode {
    int linenum;
    string value;
public:
    void getnum(int x){ linenum = x; };
    void getval(string x) { value = x; };
    int outnum (){ return linenum; };
    string outval(){ return value;};
    
    HashNode (){ };
};


#endif