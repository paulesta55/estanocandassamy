//
// Created by paul on 28/10/18.
//

#include "MoveCommand.h"
#include "engine.h"

using namespace engine;
using namespace std;
using namespace state;

MoveCommand::MoveCommand(state::Orientation o, unsigned int id) {
    orientation = o;
    this->idPlayer = id;
}

void MoveCommand::execute(state::State &state) {

}
