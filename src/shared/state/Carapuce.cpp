//
// Created by paul on 10/10/18.
//
#include <memory>

#include "Carapuce.h"

using namespace state;
using namespace std;


Carapuce::Carapuce(Orientation orientation, unsigned int currentLife, Position position, bool alive) {
    this->currentLife = currentLife;
    this->position = position;
    this->alive = alive;
    this->orientation = orientation;
    fullLife = 200;
    this->type = PokeType ::CARAPUCE;

}
