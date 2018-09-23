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
        shared_ptr<std::vector<sf::Texture>> textureCache;
    private:

        std::string mapJsonPath     = "";
        int tileWidth     = 0;
        int tileHeight     = 0;
        int widthMapNorm, heightMapNorm = 0;
        int widthMapPx, heightMapPx = 0;
        std::string tileSetPath, tileSetImagePath     = "";
        uint tileSetColumns = 0;
        // Operations
        bool pixelPicker(sf::Image image, uint tileIndex);
    public:
        PixelsLoader (std::string mapJsonPath, std::string tileSetPath, std::string tileSetImagePath);
        bool init ();
        sf::Color getPixel (int pixelNb);
        // Setters and Getters
    };


#endif //ESTANOCANDASSAMY_LOADER_H
