//
// Created by paul on 27/09/18.
//

#include "Pokemon.h"
#include "state.h"

using namespace std;
using namespace state;

std::string Pokemon::getName() {
    return this->name;
}

uint Pokemon::getFullLife() {
    return this->fullLife;
}


int Pokemon::getPokeId() {
    return this->pokeId;
}

