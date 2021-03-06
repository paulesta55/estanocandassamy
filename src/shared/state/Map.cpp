//
// Created by paul on 25/09/18.
//

#include "Map.h"
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <algorithm>
#include <string>
#include "CustomException.h"

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

shared_ptr<TileSet> Map::getTileSet() {
    return this->tileSet;
}

std::shared_ptr<vector<Layer>> Map::getLayers() {
    return this->layers;
}

Map::Map(std::string mapPath) {
    //open the map.json file
    if(mapPath.find(".json") == string::npos)
    {

        throw CustomException((char*)("not json file exception"));
    }

    try {
        ifstream ifsMap(mapPath,std::ifstream::in);
//            cout << "can open file" << endl;
        Json::Reader reader;
        Json::Value obj;

        // parse the the map.json file
        if( reader.parse(ifsMap, obj))
        {

            this->width= obj["width"].asUInt();
//        cout << "width: " << this->width << endl;

            this->height = obj["height"].asUInt();
//        cout << "height: " << this->height << endl;

            this->tileWidth = obj["tilewidth"].asUInt();
//        cout << "tilewidth: " << this->tileWidth << endl;

            const Json::Value& layers = obj["layers"];

//        cout << "nb layers : " << layers.size() << endl;

            this->tileHeight = obj["tileheight"].asUInt();

            if(this->width == 0 || this->height ==0 || this->tileWidth == 0 || this->tileHeight == 0) {
                throw                     CustomException((char*)"Bad map exception");
                ;
            }
            this->layers = make_shared<vector<Layer>>();

            try{
                //parse the layers
                for (uint i =0 ;i < layers.size();i++)
                {
                    uint height = layers[layers.size()-i-1]["height"].asUInt();
                    uint width = layers[layers.size()-i-1]["width"].asUInt();

                    if(height == 0 || width == 0 )
                    {
                        throw CustomException((char*)"bad layer dimensions exception : height or width undefined");
                    }
                    //parse layer data
                    const Json::Value& dataValue = layers[i]["data"];


                    //create a ptr vector for data
                    shared_ptr<vector<uint>> data;
                    data.reset(new vector<uint>());

                    for (uint k = 0; k < dataValue.size(); k++)

                    {   data->push_back(dataValue[k].asUInt());



                    }

                    string name = layers[i]["name"].asString();

//                        cout << "layer name : " << name << endl;

                    int x = layers[i]["x"].asInt();
                    int y = layers[i]["y"].asInt();


                    if((data.get()->size())<=0){
                        throw CustomException((char*)"Bad data layer exception");
                    }

                    this->layers.get()->emplace_back(data,height,width,x,y,name);

                }

                const Json::Value& tilesets = obj["tilesets"];

                std::string tilesetSource = tilesets[0]["source"].asString();

                //delete the tsx extension cause we converted to json
                ulong ind = tilesetSource.find("tsx");
                if(ind != string::npos)
                {
                    tilesetSource.replace(ind, 3, "json");
                }


                //create a new ptr for the tileset
                this->tileSet = make_shared<TileSet>(tilesets[0]["firstgid"].asInt(),tilesetSource);
            }
            catch(CustomException& exception2)
            {
                throw exception2;
            }
            catch(exception& e)
            {
                cerr << e.what() << endl;
                throw CustomException((char*)"cannot parse layers exception");
            }

        }
        else{
            throw CustomException((char*)"Bad Json exception");
        }

    }

    catch(ios_base::failure& failure)
    {
        throw failure;
    }
    catch(CustomException& exception2)
    {
        cerr << exception2.what() << endl;
        throw exception2;
    }
    catch(runtime_error& runtime_error1)
    {
        throw runtime_error1;
    }
    catch(exception& e)
    {
        cerr << e.what() << endl;
        throw CustomException((char*)"cannot open file exception");
    }

}

