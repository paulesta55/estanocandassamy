//
// Created by paul on 26/10/18.
//

#include "PokeRender.h"


//
// Created by paul on 24/10/18.
//
#include "PokeRender.h"
#include "state.h"
#include "render.h"
#include <iostream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
using namespace std;
using namespace render;
using namespace state;

void render::PokeRender::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = this->m_tileset.get();

    // draw the vertex array
    target.draw(m_vertices, states);
}

bool PokeRender::load(std::shared_ptr<sf::Texture> tileset, sf::Vector2u tileSize, state::Pokemon &pokemon) {
    m_tileset = tileset;
    cout << pokemon.type << endl;

    int type = pokemon.type;
    uint tileNumber = 0;

    switch (type) {
        case 0://bulbizarre
            tileNumber = 12;
            break;
        case 1://salameche
            tileNumber = 33;
            break;
        case 2://carapuce
            tileNumber = 54;
            break;
        default:
            throw new runtime_error("pokemon rendering error");
            break;

    }
    tileNumber += pokemon.orientation;
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


