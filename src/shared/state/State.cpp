//
// Created by paul on 28/09/18.
//

#include "State.h"

using namespace state;
using namespace std;

std::shared_ptr<std::vector<Player*>> State::getPlayers() {return players;}

std::shared_ptr<Map> State::getMap() {return this->map;}

State::State(Position center,shared_ptr<Map> map) : map(map), center(center){
    players.reset(new vector<Player*>());
    epoch = 0;
}

void State::setMap(std::shared_ptr<state::Map> map) {this->map = map;}

void State::setEpoch(uint &epoch) {this->epoch = epoch;}

uint State::getEpoch() {return epoch;}