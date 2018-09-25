//
// Created by paul on 22/09/18.
//

#ifndef ESTANOCANDASSAMY_LOADER_H
#define ESTANOCANDASSAMY_LOADER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string.h>


using namespace std;

    /// class PixelsLoader -
    class PixelsLoader {
        // Attributes
    public:
        shared_ptr<std::vector<sf::Texture>> textureCache = nullptr;
    private:


        uint tileWidth     = 0;
        uint tileHeight     = 0;
        std::string tileSetPath    = "";
        uint tileSetColumns = 0;
        uint tileCount = 0;
        string tilesetImageName = "";
        // Operations
        bool pixelPicker(sf::Image image, uint tileIndex);
    public:
        PixelsLoader (std::string tileSetPath);
        bool init ();
        ~PixelsLoader();
        // Setters and Getters
        uint getTileCount();
        uint getTileSetColumns();
        uint getTileWidth();
        uint getTileHeight();
    };


#endif //ESTANOCANDASSAMY_LOADER_H
