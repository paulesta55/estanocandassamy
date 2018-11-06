#include <utility>

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

uint Player::getID() {
    return this->ID;
}

void Player::setID(uint& ID) {
    this->ID = ID;
}



shared_ptr<Pokemon> Player::getPokemon() {
   return this->pokemon;
}

std::string Player::getName() { return this->name;}

Player::Player(bool IA, std::string& name, uint& ID, shared_ptr<Pokemon> pokemon): IA(IA),name(name), ID(ID), pokemon(
        std::move(pokemon)) {}

Player::~Player() {

}


