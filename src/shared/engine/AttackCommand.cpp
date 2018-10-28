//
// Created by paul on 28/10/18.
//
#include "AttackCommand.h"
#include "state.h"
#include <memory>
using namespace engine;
using namespace std;

AttackCommand::AttackCommand(unsigned int idAttacked, unsigned int  idPlayer): idPlayer(idPlayer), idAttacked(idAttacked) {}


void AttackCommand::execute(state::State &state) {
    unique_ptr<state::State> state_ptr;
    state_ptr.reset( &state);

}

