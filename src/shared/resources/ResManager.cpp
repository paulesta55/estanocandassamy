//
// Created by paul on 25/09/18.
//

#include "ResManager.h"
#include <iostream>
#include <fstream>
#include <json/json.h>
#include "state.h"
using namespace state;
using namespace std;
using namespace resources;

ResManager::ResManager(string tileSetPath): tileSetPath(tileSetPath) {
    this->textureCache.reset(new std::vector<sf::Texture> );
}

using namespace std;

/**
 * Fill the textureCache with tiles of the given tileset (specified by tileSetPath)
 * @return true if the process worked
 */
bool ResManager::init() {
    // open the tileSet metadata file
    ifstream ifsTiles(this->tileSetPath);

    Json::Reader reader;
    Json::Value obj;

    // parse the the json file
    if( reader.parse(ifsTiles, obj)) {
        this->tileSetColumns = obj["columns"].asUInt();
        cout << "nb columns " << this->tileSetColumns << endl;
        this->tileCount = obj["tilecount"].asUInt();
        cout << "nb tiles " << this->tileCount << endl;
        this->tileWidth = obj["tilewidth"].asUInt();
        cout << this->tileWidth << endl;
        this->tileHeight = obj["tileheight"].asUInt();
        this->tilesetImageName = obj["image"].asString();
        // fill the cache with tiles' textures
        this->textureCache.get()->reserve(this->tileCount);


        // open the tileset image
        sf::Image tileSetImage;
        tileSetImage.loadFromFile("res/"+tilesetImageName);

        // fill the cache with pixelPicker method
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

ResManager::~ResManager() {
    this->textureCache.reset();
}

uint ResManager::getTileCount() {
    return this->tileCount;
}

uint ResManager::getTileSetColumns() {
    return this->tileSetColumns;
}

uint ResManager::getTileWidth() {
    return this->tileWidth;
}

/**
 * Load the tile of index tileIndex in the tileset in the @code{textureCache}
 * @param image tilesetImage
 * @param tileIndex tile loaded
 * @return true if the process worked
 */
bool ResManager::pixelPicker(sf::Image image, uint tileIndex) {
    sf::Texture texture;
    sf::Sprite sprite;

    // set the first element at (0,0)
    uint yIndex = 0;
    uint xIndex = tileIndex-1;

    // compute the tile normalized position (xIndex,yIndex)
    if (tileIndex > this->tileSetColumns ) {
        yIndex   = (tileIndex - 1)/tileSetColumns;
        xIndex = xIndex - yIndex * this->tileSetColumns;

    }
//    cout << "yIndex " << yIndex <<endl;
//    cout << "xIndex " << xIndex << endl;

    // compute tile position in pixels
    uint xPx = xIndex + 1 + xIndex * tileWidth;
    uint yPx = yIndex + 1 + yIndex * tileHeight;

    // get the tile from tileset image
    texture.loadFromImage(image,sf::IntRect(xPx,yPx,tileWidth,tileHeight));

    // store the image in the cache
    this->textureCache.get()->push_back(texture);
//    cout << "tile number " << tileIndex << " ok" << endl;

    return true;
}

uint ResManager::getTileHeight() {
    return this->tileHeight;
}
