//
// Created by paul on 10/10/18.
//
#include <memory>

#include "Carapuce.h"

using namespace state;
using namespace std;

Carapuce::Carapuce(uint& pokeId, Orientation orientation,  uint currentLife, state::Position position, bool alive) {
    this->currentLife = currentLife;
    this->position = position;
    this->alive = alive;
    this->pokeId = pokeId;
    fullLife = 200;
    this->orientation = orientation;
}



