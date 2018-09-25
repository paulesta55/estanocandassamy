//
// Created by paul on 25/09/18.
//

#include "ResManager.h"
#include <iostream>
#include <fstream>
#include <json/json.h>

state::ResManager::ResManager(std::string tileSetPath): tileSetPath(tileSetPath) {
    this->textureCache.reset(new std::vector<sf::Texture> );
}

using namespace std;

bool state::ResManager::init() {
    ifstream ifsTiles(this->tileSetPath);

    Json::Reader reader;
    Json::Value obj;
    if( reader.parse(ifsTiles, obj)) {
        this->tileSetColumns = obj["columns"].asUInt();
        cout << "nb columns" << this->tileSetColumns << endl;
        this->tileCount = obj["tilecount"].asUInt();
        cout << "nb tiles " << this->tileCount << endl;
        this->tileWidth = obj["tilewidth"].asUInt();
        cout << this->tileWidth << endl;
        this->tileHeight = obj["tileheight"].asUInt();
        this->tilesetImageName = obj["image"].asString();
        // fill the cache with tiles' textures
        this->textureCache.get()->reserve(this->tileCount);


        sf::Image tileSetImage;
        tileSetImage.loadFromFile("res/"+tilesetImageName);

        for(uint i=1; i<=this->tileCount;i++) {
            this->pixelPicker(tileSetImage,i);
        }
        ifsTiles.close();
        return true;
    }
    else {
        cout << "cannot parse tileset" << endl;
        cout << reader.getFormattedErrorMessages() << endl;

    }
    return false;
}

state::ResManager::~ResManager() {
    this->textureCache.reset();
}

uint state::ResManager::getTileCount() {
    return this->tileCount;
}

uint state::ResManager::getTileSetColumns() {
    return this->tileSetColumns;
}

uint state::ResManager::getTileWidth() {
    return this->tileWidth;
}

bool state::ResManager::pixelPicker(sf::Image image, uint tileIndex) {
    sf::Texture texture;
    sf::Sprite sprite;

    uint yIndex = 0;
    uint xIndex = tileIndex-1;


    if (tileIndex > this->tileSetColumns ) {
        yIndex   = (tileIndex - 1)/tileSetColumns;
        xIndex = xIndex - yIndex * this->tileSetColumns;

    }
    cout << "yIndex " << yIndex <<endl;
    cout << "xIndex " << xIndex << endl;
    uint xPx = xIndex + 1 + xIndex * tileWidth;
    uint yPx = yIndex + 1 + yIndex * tileHeight;

    // get the tile from tileset image
    texture.loadFromImage(image,sf::IntRect(xPx,yPx,tileWidth,tileHeight));
    this->textureCache.get()->push_back(texture);
    cout << "tile number " << tileIndex << endl;

    return true;
}

uint state::ResManager::getTileHeight() {
    return this->tileHeight;
}
