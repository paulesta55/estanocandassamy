//
// Created by paul on 25/09/18.
//

#include "TileSet.h"

using namespace std;
using namespace state;

state::TileSet::TileSet(int firstGID, std::string source): firstGID(firstGID), source(source) {}

std::string state::TileSet::getSource() {
    return this->source;
}

int TileSet::getFirstGID() {
    return this->firstGID;
}
