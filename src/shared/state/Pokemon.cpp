//
// Created by paul on 27/09/18.
//

#include "Pokemon.h"
#include "state.h"

using namespace std;
using namespace state;

std::vector<int> state::Pokemon::getPosition() {
    return this->position;
}

int Pokemon::getCurrentLife() {
    return this->currentLife;
}

void Pokemon::setPosition(std::vector<int> position) {
    this->position = position;

}

void Pokemon::setCurrentLife(int currentLife) {
    this->currentLife = currentLife;
}

Pokemon::Pokemon(std::vector<int> position, int currentLife, std::string name): position(position),currentLife(currentLife),name(name) {

}
