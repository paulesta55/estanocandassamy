//
// Created by paul on 25/09/18.
//

#include "Map.h"


using namespace state;
using namespace std;


state::Map::Map(std::vector<Layer> layers, TileSet tileset, uint height, uint width, uint tileWidth,
                uint tileHeight): layers(layers),tileSet(tileSet),height(height),width(width),tileWidth(tileWidth),
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

TileSet Map::getTileSet() {
    return this->getTileSet();
}

std::vector<Layer> Map::getLayers() {
    return this->layers;
}
