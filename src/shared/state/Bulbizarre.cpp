//
// Created by paul on 10/10/18.
//

#include "Bulbizarre.h"

using namespace std;
using namespace state;

Bulbizarre::Bulbizarre(std::string &name, int &pokeId, uint currentLife, state::Position position, bool alive) {
    this->name = name;
    this->currentLife = currentLife;
    this->position = position;
    this->alive = alive;
    this->race = "Bulbizarre";
    this->raceId = 2;
    this->pokeId = pokeId;
    fullLife = 250;
}


void Bulbizarre::heal() {
    if (currentLife <= fullLife-20)
    {
        currentLife += 20;
    }
}