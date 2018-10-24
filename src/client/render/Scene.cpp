#include <utility>

//
// Created by paul on 22/10/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.h"
#include "CustomException.h"
#include "render.h"
#include <iostream>
using namespace std;
using namespace render;

Scene::Scene(shared_ptr<state::State> state1,string tileSet) {
    //good dimensions : 620 x 620
    sf::RenderWindow window(sf::VideoMode(620,620),"test window");
    vector<shared_ptr<LayerRender>> layerVec;
    this->state = std::move(state1);
    uint tileWidth = this->state->getMap()->getTileWidth();
    uint tileHeight = this->state->getMap()->getTileHeight();
    for(auto layer: *(this->state->getMap()->getLayers()))
    {
        shared_ptr<LayerRender> layerRend;
        layerRend.reset(new LayerRender());

        if(!(layerRend->load(tileSet,sf::Vector2u(tileWidth,tileHeight),
                layer.getData(),layer.getWidth(),layer.getHeight()))) throw  runtime_error("bad layer rendering");
        layerVec.push_back(layerRend);
    }
    string tileset2 = "res/src/tilestPokemon.png";
    vector<shared_ptr<PokeRender>> layerPoke;
    for( auto player : *(this->state->getPlayers()))
    {
        shared_ptr<PokeRender> pokeRender;
        pokeRender.reset(new PokeRender());
        if(player->getPokemon()){
            state::Pokemon pokemon = *(player->getPokemon());
            if(!(pokeRender->load(tileset2,sf::Vector2u(tileWidth,tileHeight),pokemon))) throw runtime_error("bad pokemon rendering");
            layerPoke.push_back(pokeRender);
        }

    }
    while(window.isOpen()){
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for(auto layerRend : layerVec)
        {
            window.draw(*layerRend);
        }
        for(auto pokeRend: layerPoke)
        {
            window.draw(*pokeRend);
        }

        // good dimensions 200x200
        sf::View view2(sf::Vector2f(240.f, 300.f), sf::Vector2f(700.f, 700.f));

        window.setView(view2);

        window.display();
    }
}
