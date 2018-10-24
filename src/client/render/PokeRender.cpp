//
// Created by paul on 24/10/18.
//

#include "PokeRender.h"
#include "state.h"
#include "state/Orientation.h"
#include "state/PokeType.h"
#include <iostream>
using namespace state;
using namespace std;

bool render::PokeRender::load(const std::string &tileset, sf::Vector2u tileSize, state::Pokemon &pokemon) {
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    uint tileNumber = 0;

    switch(pokemon.getType()){
//        case  PokeType ::BULBIZARRE:
//            tileNumber= 13;
//            break;
//        case PokeType ::SALAMECHE:
//            tileNumber = 34;
//            break;
//        case PokeType :: CARAPUCE:
//            tileNumber= 55;
//            break;
        default:
            cout << pokemon.getType() << endl;
    }
    cout << pokemon.getType() <<endl;
    int pokeO = static_cast<int>(pokemon.getOrientation());
    switch(pokeO)
    {
        case SOUTH:
            break;
        case NORTH:
            tileNumber++;
            break;
        case WEST:
            tileNumber+=2;
            break;
        case EST:
            tileNumber+=3;
            break;
    }
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);


    // find its position in the tileset texture
    int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
    int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

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

void render::PokeRender::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}
