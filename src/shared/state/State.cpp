//
// Created by paul on 28/09/18.
//

#include "State.h"

using namespace state;
using namespace std;

Map* State::getMap() {
    return this->map;
}

std::vector<Player*> State::getPlayers() {
    return this->players;
}