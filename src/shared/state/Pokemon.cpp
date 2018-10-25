//
// Created by paul on 27/09/18.
//

#include "Pokemon.h"
#include "state.h"
using namespace std;
using namespace state;


uint Pokemon::getPokeId() {
    return this->pokeId;
}

string Pokemon::getType() {
    return this->type;
}


void Pokemon::setCurrentLife(uint& currentLife) { this->currentLife=(uint)currentLife;}

Position Pokemon::getPosition() {
    return position;
}

void Pokemon::setPosition(Position &pos) {
    position = pos;
}

uint Pokemon::getCurrentLife() {
    return currentLife;
}

bool Pokemon::getAlive() {
    return alive;
}

void Pokemon::setAlive(bool alive) {
    this->alive = alive;
}

string Pokemon::getOrientation() {
    return this->orientation;
}

void Pokemon::setOrientation(string orientation) {
    this->orientation = orientation;
}

uint Pokemon::getFullLife() {
    return this->fullLife;
}
