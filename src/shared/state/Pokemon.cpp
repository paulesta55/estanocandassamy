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

Pokemon::~Pokemon() {

}

uint Pokemon::getFullLife() {
    return this->fullLife;
}

int Pokemon::getRaceId() {
    return this->raceId;
}

std::string Pokemon::getRace() {
    return this->race;
}

int Pokemon::getPokeId() {
    return this->pokeId;
}
