//
// Created by paul on 22/09/18.
//

#include <PixelsLoader.h>
#include <fstream>
#include <json/json.h>
#include "PixelsLoader.h"


sf::Color PixelsLoader::getPixel(int pixelNb) {
    return sf::Color();
}

bool PixelsLoader::init() {

    uint tilecount = 0;
    cout << this->mapJsonPath << endl;
    ifstream ifsMap(this->mapJsonPath);
    ifstream ifsTiles(this->tileSetPath);

    sf::Image tileSetImage;
    tileSetImage.loadFromFile(this->tileSetImagePath);


    Json::Reader reader;
    Json::Value obj;


    Json::Reader reader2;
    Json::Value obj2;
    if( reader2.parse(ifsTiles, obj2)) {
        this->tileSetColumns = obj2["columns"].asUInt();
        cout << "nb columns" << this->tileSetColumns << endl;
        tilecount = obj2["tilecount"].asUInt();

    }
    else {
        cout << "cannot parse tileset" << endl;
        cout << reader2.getFormattedErrorMessages() << endl;
    }
    if(reader.parse(ifsMap, obj)) {
        cout << "map height : " << obj["height"].asInt() << endl;
        this->heightMapNorm = obj["height"].asInt();
        this->widthMapNorm = obj["width"].asInt();
        cout << "map width : " << obj["width"].asInt() << endl;
        this->tileHeight = obj["tileheight"].asInt();
        this->tileWidth = obj["tilewidth"].asInt();
        cout << "tile size :" << this->tileWidth << "px" << endl;
        auto layers = obj["layers"];

        auto layer = layers[0];
        auto data = layer["data"];
        this->textureCache.get()->reserve(tilecount);

        for(uint i=1; i<=tilecount;i++) {
            this->pixelPicker(tileSetImage,i);
        }

//        this->pixelPicker(tileSetImage,25);

        return true;
    }



    else{
        cout << reader.getFormatedErrorMessages() << endl;
    }





    return false;
}



PixelsLoader::PixelsLoader(std::string mapJsonPath, std::string tileSetPath, string tileSetImagePath):mapJsonPath
(mapJsonPath),tileSetPath(tileSetPath), tileSetImagePath(tileSetImagePath) {
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
    texture.loadFromImage(image,sf::IntRect(xPx,yPx,tileWidth,tileHeight));
    this->textureCache.get()->push_back(texture);


//    sprite.setTexture(texture);

//    cout << "texture width : " << texture.getSize().x << endl;
//    cout << "texture heigth : " << texture.getSize().y << endl;

    cout << "tile number " << tileIndex << endl;

    return false;
}




