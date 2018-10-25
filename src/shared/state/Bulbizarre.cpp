//
// Created by paul on 10/10/18.
//

#include "Bulbizarre.h"
#include <memory>

using namespace std;
using namespace state;

Bulbizarre::Bulbizarre( uint &pokeId, string orientation,uint currentLife, state::Position position, bool alive) {
    this->currentLife = currentLife;
    this->position = position;
    this->alive = alive;
    this->type = "Bulbizarre";
    this->pokeId = pokeId;
    fullLife = 250;
    if(orientation == "south" || orientation == "north" || orientation == "west" || orientation == "est")
    {
        this->orientation= orientation;
    }
}
