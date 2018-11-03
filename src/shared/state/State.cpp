//
// Created by paul on 28/09/18.
//

#include "State.h"
#include <iostream>
using namespace state;
using namespace std;

std::map<unsigned int,shared_ptr<Player>>& State::getPlayers() {return players;}

std::shared_ptr<Map> State::getMap() {return this->map;}

State::State(Position center,shared_ptr<Map> map) : map(map), center(center){
    epoch = 0;

}

void State::setMap(std::shared_ptr<state::Map> map) {this->map.swap(map);

cout << this->getMap()->getLayers()->at(0).getName() << endl;
}

void State::setEpoch(uint &epoch) {this->epoch = epoch;}

uint State::getEpoch() {return epoch;}

