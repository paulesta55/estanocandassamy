//
// Created by paul on 10/10/18.
//

#include "Bulbizarre.h"
#include <memory>

using namespace std;
using namespace state;

Bulbizarre::Bulbizarre( uint &pokeId, Orientation orientation,uint currentLife, state::Position position, bool alive) {
    this->currentLife = currentLife;
    this->position = position;
    this->alive = alive;
    this->pokeId = pokeId;
    fullLife = 250;
    this->orientation = orientation;
}
