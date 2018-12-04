//
// Created by paul on 10/10/18.
//

#include "Salameche.h"

#include <memory>

using namespace state;
using namespace std;


Salameche::Salameche(Orientation orientation, unsigned int currentLife, Position position,
                     bool alive) {
    this->currentLife = currentLife;
    this->position = position;
    this->alive = alive;
    this->orientation = orientation;
    this->type = PokeType :: SALAMECHE;
this->fullLife = 200;
}

Pokemon *Salameche::clone() const {
    return new Salameche(*this);
}
