//
// Created by paul on 28/09/18.
//

#include "Player.h"

#include "state.h"


using namespace state;
using namespace std;


bool state::Player::getIA() {
    return this->IA;
}


void Player::setIA(bool IA) {
    this->IA = IA;
}

int Player::getID() {
    return this->ID;
}

void Player::setID(int ID) {
    this->ID = ID;
}

bool Player::isAlive() {
    return this->alive;
}

void Player::setAlive(bool alive) {
    this->alive = alive;
}

shared_ptr<Pokemon> Player::getPokemon() {
   return this->pokemon;
}

Player::Player(bool IA, std::string name, int ID, shared_ptr<Pokemon> pokemon): IA(IA),name(name), pokemon(pokemon) {}


