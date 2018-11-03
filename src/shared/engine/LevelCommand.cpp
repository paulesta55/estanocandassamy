//
// Created by paul on 03/11/18.
//

#include "LevelCommand.h"
#include <iostream>
#include "state.h"
#include <string>

using namespace state;
using namespace engine;
using namespace std;


engine::LevelCommand::LevelCommand(unsigned int idLevel):idLevel(idLevel) {}

void engine::LevelCommand::execute(state::State &state) {
    State& state_ref = state;
    string  mapPath = "res/src/etage";
    mapPath+=to_string(idLevel);
    mapPath+=".json";
    shared_ptr<Map> newMap;
    newMap.reset(new Map(mapPath));
    state_ref.setMap(newMap);
}

