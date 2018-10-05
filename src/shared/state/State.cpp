//
// Created by paul on 28/09/18.
//

#include "State.h"

using namespace state;
using namespace std;

std::vector<Player*> State::getPlayers() {return this->players;}

std::shared_ptr<Map> State::getMap() {return this->map;}

State::State() {
    this->map = nullptr;
}
