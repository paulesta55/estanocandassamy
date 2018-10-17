//
// Created by paul on 10/10/18.
//

#include "Bulbizarre.h"

using namespace std;
using namespace state;

Bulbizarre::Bulbizarre(uint &pokeId, uint currentLife, state::Position position, bool alive) {
    this->currentLife = currentLife;
    this->position = position;
    this->alive = alive;
    this->name = "Bulbizarre";
    this->pokeId = pokeId;
    fullLife = 250;
}
