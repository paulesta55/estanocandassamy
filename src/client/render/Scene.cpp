
//
// Created by paul on 22/10/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.h"
#include "render.h"
#include <iostream>
#include <string>
#include "state.h"
using namespace std;
using namespace render;
using namespace state;
Scene::Scene(shared_ptr<state::State> state1,string tileSet) {

//    vector<shared_ptr<LayerRender>> layerVec;
    this->tileset=tileSet;
    string tileset2 = "res/src/tilestPokemon.png";
    this->pokeTileSet.reset(new sf::Texture());
    this->pokeTileSet->loadFromFile("res/src/tilestPokemon.png");
    this->state.reset(state1.get());
    this->updateState();



}

void Scene::draw() {

    //good dimensions : 620 x 620
    sf::RenderWindow window(sf::VideoMode(620,620),"test window");
    while(window.isOpen()){
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed :
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    this->clock.restart();
                    break;
                case sf::Event::KeyReleased:
                    cout << this->clock.getElapsedTime().asMilliseconds() << endl;
                    break;

            }
            if(event.type == sf::Event::Closed)
                window.close();

        }
        window.clear();
        for(auto layerRend : layerVec)
        {
            window.draw(*layerRend);
        }
        for(auto pokeRend: pokeVec)
        {

            window.draw(*(pokeRend.second));
        }


        // good size : 200 x 200
        sf::View view2(sf::Vector2f(this->xCenter, this->yCenter), sf::Vector2f(700.f, 700.f));
//        window.draw(text);

        window.setView(view2);
        window.display();
    }
}

void Scene::updateState() {

    this->layerVec.clear();
    if(state->getPlayers().size() <=0){
        throw new runtime_error("cannot render a state with no players");
    }
    if(!state->getMap())
    {
        throw new runtime_error("cannot render a state with no map");
    }
    uint tileWidth = this->state->getMap()->getTileWidth();
    uint tileHeight = this->state->getMap()->getTileHeight();

    this->xCenter = state->center.x*tileWidth;
    this->yCenter = state->center.y*tileHeight;
    for(auto layer: *(this->state->getMap()->getLayers()))
    {
        shared_ptr<LayerRender> layerRend;
        layerRend.reset(new LayerRender());

        if(!(layerRend->load(this->tileset,sf::Vector2u(tileWidth,tileHeight),
                             layer.getData(),layer.getWidth(),layer.getHeight()))) throw  runtime_error("bad layer rendering");
        layerVec.push_back(layerRend);
    }
    string tileset2 = "res/src/tilestPokemon.png";
//    vector<shared_ptr<PokeRender>> layerPoke;
    for( auto player :this->state->getPlayers())
    {
        shared_ptr<PokeRender> pokeRender;
        pokeRender.reset(new PokeRender());
        if(player.second->getPokemon()){
            std::shared_ptr<state::Pokemon> pokemon = player.second->getPokemon();
            if(!(pokeRender->load(this->pokeTileSet,sf::Vector2u(tileWidth,tileHeight),*pokemon))) throw runtime_error("bad pokemon rendering");
            pokeVec.insert(make_pair(player.second->getID(),pokeRender));
        }

    }
//    this->pokeVec.at(0)->setPosition(state::Position(this->pokeVec.at(0)->getPosition().x+1,this->pokeVec.at(0)->getPosition().y+1));

}

void movePokeRender(unsigned int pokeId)
{

}


void Scene::stateChanged(const state::Event& e) {

    if(e.getEventType() == TAB_EVENT )
    {
        state::TabEvent event = *(TabEvent*)(e.clone());
        switch(event.tabEventId) {
            case MOVE:
                pokeVec.at(event.playerId)->setPosition(state->getPlayers().at(event.playerId)->getPokemon()->getPosition().x);
                break;

        }
    }
    this->updateState();
}


