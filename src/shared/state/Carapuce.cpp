//
// Created by paul on 10/10/18.
//

#include "Carapuce.h"

using namespace state;
using namespace std;

Carapuce::Carapuce(std::string orientation,uint& pokeId, state::Position position, bool alive) {
    this->currentLife = currentLife;
    this->position = position;
    this->alive = alive;
    this->name = "carapuce";
    this->pokeId = pokeId;
    fullLife = 200;
    if(orientation == "south" || orientation == "north" || orientation == "west" || orientation == "est")
    {
        this->orientation= orientation;
    }
}



