//
// Created by paul on 28/09/18.
//
#include "Pokedata.h"
#include "stdio.h"

using namespace state;
using namespace std;


Pokedata::Pokedata(uint fullLife, std::string type, std::vector<std::string> skills, uint typeID): fullLife(fullLife), type(type),
skills(skills), typeID(typeID) {}


uint Pokedata::getFullLife() {
    return this->fullLife;
}

std::string Pokedata::getType() {
    return this->type;
}

std::vector<std::string> Pokedata::getSkills() {
    return this->skills;
}

uint Pokedata::getTypeID() {
    return this->typeID;
}