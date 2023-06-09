//Bryan Kim
//pet.cpp
//Pet class definitions

#include "pet.h"

//desc: constructor
//pre : none
//post: -0 denotes cat, 1 denotes dog, -1 denotes uninitialized 
Pet::Pet(int type, string name) {
    this->type = type;
    this->name = name;
}

//desc: settter for type
void Pet::setType(int type) {
    this->type = type;
}

//desc: setter for name
void Pet::setName(string name) {
    this->name = name;
}

//desc: getter for type
int Pet::getType() {
    return type;
}

//desc: getter for name
string Pet::getName() {
    return name;
}