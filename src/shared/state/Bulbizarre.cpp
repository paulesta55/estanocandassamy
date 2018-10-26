//
// Created by paul on 10/10/18.
//

#include "Bulbizarre.h"
#include <memory>

using namespace std;
using namespace state;



Bulbizarre::Bulbizarre(unsigned int &ID, Orientation orientation, unsigned int currentLife, Position position,
                       bool alive) {

    this->ID = ID;
    this->currentLife = currentLife;
    this->position = position;
    this->alive = alive;
    this->orientation = orientation;
    this->type = PokeType ::BULBIZARRE;
    fullLife = 250;
}
