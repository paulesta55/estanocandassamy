//
// Created by paul on 25/09/18.
//

#include "MapLoader.h"
#include "state.h"

using namespace state;
using namespace std;
using namespace resources;


MapLoader::MapLoader(string metaMapPath) {

}

bool MapLoader::load() {
    return false;
}

MapLoader::~MapLoader() {
    this->map.reset();
}
