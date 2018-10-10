//
// Created by paul on 28/09/18.
//

#include "State.h"

using namespace state;
using namespace std;

std::shared_ptr<std::vector<Player*>> State::getPlayers() {return this->players;}

std::shared_ptr<Map> State::getMap() {return this->map;}

State::State(shared_ptr<Map> map) : map(map){
    players.reset(new vector<Player*>());
}