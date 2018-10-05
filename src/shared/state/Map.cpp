//
// Created by paul on 25/09/18.
//

#include "Map.h"
#include <iostream>
#include <fstream>
#include <json/json.h>

using namespace state;
using namespace std;




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
    return this->tileSet;
}

std::vector<Layer> Map::getLayers() {
    return this->layers;
}

Map::Map(std::string mapPath) {
    //open the map.json file
    ifstream ifsMap(mapPath);

    Json::Reader reader;
    Json::Value obj;

    // parse the the map.json file
    if( reader.parse(ifsMap, obj))
    {
        this->width= obj["width"].asUInt();
        cout << "width: " << this->width << endl;

        this->height = obj["height"].asUInt();
        cout << "height: " << this->height << endl;

        this->tileWidth = obj["tilewidth"].asUInt();
        cout << "tilewidth: " << this->tileWidth << endl;

        const Json::Value& layers = obj["layers"];
        this->tileHeight = obj["tileheight"].asUInt();
        for (int i =0 ;i < layers.size();i++)
        {
            uint height = layers[layers.size()-i-1]["height"].asUInt();
            uint width = layers[layers.size()-i-1]["width"].asUInt();


            const Json::Value& dataValue = layers[layers.size()-i]["data"];
            shared_ptr<vector<uint>> data;
            data.reset(new vector<uint>(layers.size()));

            for (int k = 0; k < dataValue.size(); k++)
            {
                data->push_back(dataValue[k].asUInt());
            }

            string name = layers[layers.size()-i-1]["name"].asString();

            int x = layers[layers.size()-i-1]["x"].asInt();
            int y = layers[layers.size()-i-1]["y"].asInt();


            this->layers.emplace_back(data,height,width,x,y,name);

            data.reset();

        }
    }
}
