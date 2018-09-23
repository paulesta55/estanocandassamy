//
// Created by paul on 22/09/18.
//

#include <PixelsLoader.h>
#include <fstream>
#include <json/json.h>
#include "PixelsLoader.h"


bool PixelsLoader::init() {

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
//    if(reader.parse(ifsMap, obj)) {
//        cout << "map height : " << obj["height"].asInt() << endl;
//        this->heightMapNorm = obj["height"].asUInt();
//        this->widthMapNorm = obj["width"].asUInt();
//        cout << "map width : " << obj["width"].asInt() << endl;
//        this->tileHeight = obj["tileheight"].asUInt();
//        this->tileWidth = obj["tilewidth"].asUInt();
//        cout << "tile size :" << this->tileWidth << "px" << endl;
//        auto layers = obj["layers"];
//
//        auto layer = layers[0];
//        auto data = layer["data"];
//        this->textureCache.get()->reserve(this->tileCount);
//
//        for(uint i=1; i<=this->tileCount;i++) {
//            this->pixelPicker(tileSetImage,i);
//        }
//
//        ifsMap.close();
//        ifsTiles.close();
//        return true;
//    }
//
//
//
//    else{
//        cout << reader.getFormatedErrorMessages() << endl;
//    }
//
//
//
//
//
//    return false;
}



PixelsLoader::PixelsLoader(std::string tileSetPath): tileSetPath(tileSetPath) {
    this->textureCache.reset( new std::vector<sf::Texture>);
}


bool PixelsLoader::pixelPicker(sf::Image image, uint tileIndex) {

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

    return false;
}

PixelsLoader::~PixelsLoader() { this->textureCache.reset(); }

uint PixelsLoader::getTileCount() {return this->tileCount;}

uint PixelsLoader::getTileSetColumns() { return this->tileSetColumns; }

uint PixelsLoader::getTileWidth() { return this->tileWidth; }

uint PixelsLoader::getTileHeight() { return this->tileHeight; }

