//
// Created by paul on 24/10/18.
//
#include "PokeRender.h"
#include "state.h"

#include <iostream>

using namespace state;
using namespace std;
using namespace render;
//bool render::PokeRender::load(const std::string &tileset, sf::Vector2u tileSize, state::Pokemon &pokemon) {
//    // load the tileset texture
//    if (!m_tileset.loadFromFile(tileset))
//        return false;


//    const char* poketype = pokemon.getType().c_str();
//    if(strcmp(poketype,"Bulbizarre")==0) {
//        tileNumber = 12;
//    }
//    if(strcmp(poketype,"Salameche")==0) {
//        tileNumber = 33;
//    }
//    if(strcmp(poketype,"Carapuce")==0)
//    {
//        tileNumber = 54;
//    }


//    const char* orientation = pokemon.getOrientation().c_str();
//    if(strcmp(orientation,"north")==0) {
//        tileNumber++;
//    }
//    if(strcmp(orientation,"west")==0) {
//        tileNumber +=2 ;
//    }
//    if(strcmp(poketype,"est")==0)
//    {
//        tileNumber += 3;
//    }
//    switch(pokemon.getType()){
//        case  PokeType ::BULBIZARRE:
//            tileNumber= 13;
//            break;
//        case PokeType ::SALAMECHE:
//            tileNumber = 34;
//            break;
//        case PokeType :: CARAPUCE:
//            tileNumber= 55;
//            break;
//        default:
//            cout << pokemon.getType() << endl;
//    }
//    cout << pokemon.getType() <<endl;
//    int pokeO = static_cast<int>(pokemon.getOrientation());
//    switch(pokeO)
//    {
//        case SOUTH:
//            break;
//        case NORTH:
//            tileNumber++;
//            break;
//        case WEST:
//            tileNumber+=2;
//            break;
//        case EST:
//            tileNumber+=3;
//            break;
//    }



//    return true;
//}

void render::PokeRender::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = this->m_tileset.get();;

    // draw the vertex array
    target.draw(m_vertices, states);
}

bool PokeRender::load(std::shared_ptr<sf::Texture> tileset, sf::Vector2u tileSize, state::Pokemon &pokemon) {
    m_tileset = tileset;
    uint tileNumber = 0;
    cout << pokemon.type << endl;

    switch (pokemon.type) {
        case PokeType ::BULBIZARRE:
            tileNumber = 12;
            break;
        case PokeType :: SALAMECHE:
            tileNumber = 33;
            break;
        case PokeType ::CARAPUCE:
            tileNumber = 54;
            break;
        default:
            throw new runtime_error("pokemon rendering error");
            break;

    }


    cout << pokemon.orientation << endl;
    switch (pokemon.orientation){
        case Orientation :: SOUTH:
            break;
        case Orientation ::NORTH:
            tileNumber++;
            break;
        case Orientation ::WEST:
            tileNumber+=2;
            break;
        case Orientation :: EST:
            tileNumber+=3;
            break;
        default:
            throw new runtime_error("pokemon orientation rendering error");
            break;
    }
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);


    // find its position in the tileset texture
    int tu = tileNumber % (m_tileset->getSize().x / tileSize.x);
    int tv = tileNumber / (m_tileset->getSize().x / tileSize.x);

    // get a pointer to the current tile's quad
    sf::Vertex* quad = &m_vertices[0];

    // define its 4 corners
    quad[0].position = sf::Vector2f(pokemon.getPosition().x* tileSize.x, pokemon.getPosition().y * tileSize.y);
    quad[1].position = sf::Vector2f((pokemon.getPosition().x + 1) * tileSize.x, pokemon.getPosition().y * tileSize.y);
    quad[2].position = sf::Vector2f((pokemon.getPosition().x + 1) * tileSize.x, (pokemon.getPosition().y + 1) * tileSize.y);
    quad[3].position = sf::Vector2f(pokemon.getPosition().x * tileSize.x, (pokemon.getPosition().y + 1) * tileSize.y);

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f(tu * (tileSize.x+1)+1, tv * (tileSize.y+1)+1);
    quad[1].texCoords = sf::Vector2f((tu + 1) * (tileSize.x+1), tv * (tileSize.y+1)+1);
    quad[2].texCoords = sf::Vector2f((tu + 1) * (tileSize.x+1), (tv + 1) * (tileSize.y+1));
    quad[3].texCoords = sf::Vector2f(tu * (tileSize.x+1)+1, (tv + 1) * (tileSize.y+1));


    return true;
}
