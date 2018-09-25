//
// Created by paul on 25/09/18.
//

#include "Map.h"


using namespace state;
using namespace std;

state::Map::Map(std::vector<Layer> layers, std::vector<TileSet> tileSets, uint height, uint width, uint tileWidth,
                uint tileHeight): layers(layers),tileSets(tileSets),height(height),width(width),tileWidth(tileWidth),
                tileHeight(tileHeight){}

uint Map::getTileHeight() {
    return this->tileHeight;
}

uint Map::getTileWidth() {
    return this->tileWidth;
}

uint Map::getWidth() {
    return this->width;
}

uint Map::getHeight() {
    return this->height;
}

std::vector<TileSet> Map::getTileSets() {
    return this->getTileSets();
}

std::vector<Layer> Map::getLayers() {
    return this->layers;
}
