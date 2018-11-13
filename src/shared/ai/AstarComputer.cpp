//
// Created by paul on 13/11/18.
//
#include <memory>
#include "AstarComputer.h"

using namespace std;
using namespace state;
using namespace ai;

ai::AstarComputer::AstarComputer(state::Map &map, Node objectif, Node source): objectif(objectif),source(source){
    this->map = make_shared<Map>(map);
}

