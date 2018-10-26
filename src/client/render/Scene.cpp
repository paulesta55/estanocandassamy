#include <utility>

//
// Created by paul on 22/10/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.h"
#include "CustomException.h"
#include "render.h"
#include <iostream>
#include <string>
using namespace std;
using namespace render;

Scene::Scene(shared_ptr<state::State> state1,string tileSet) {


//    vector<shared_ptr<LayerRender>> layerVec;
    this->tileset =tileSet;
    this->state = std::move(state1);
    if(state->getPlayers()->size() <=0){
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
    for( auto player : *(this->state->getPlayers()))
    {
        shared_ptr<PokeRender> pokeRender;
        pokeRender.reset(new PokeRender());
        if(player->getPokemon()){
            state::Pokemon pokemon = *(player->getPokemon());
            if(!(pokeRender->load(tileset2,sf::Vector2u(tileWidth,tileHeight),pokemon))) throw runtime_error("bad pokemon rendering");
            pokeVec.push_back(pokeRender);
        }

    }



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

            window.draw(*pokeRend);
        }

//        sf::Font font;
//        font.loadFromFile("res/src/arial.ttf");
//
//        sf::Text text;
//        text.setFont(font);
//        text.setString("close the window to \n display an other state");
//        // choix de la taille des caractères
//        text.setCharacterSize(10); // exprimée en pixels, pas en points !
//
//// choix de la couleur du texte
//        text.setColor(sf::Color::Black);
//
//// choix du style du texte
//        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
//        text.setPosition(sf::Vector2f(x-5, y));


        // good size : 200 x 200
        sf::View view2(sf::Vector2f(this->xCenter, this->yCenter), sf::Vector2f(200.f, 200.f));
//        window.draw(text);

        window.setView(view2);
        window.display();
    }
}

void Scene::updateState(std::shared_ptr<state::State> state1) {
    this->layerVec.clear();
    this->pokeVec.clear();
    this->state = std::move(state1);
    if(state->getPlayers()->size() <=0){
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
    for( auto player : *(this->state->getPlayers()))
    {
        shared_ptr<PokeRender> pokeRender;
        pokeRender.reset(new PokeRender());
        if(player->getPokemon()){
            state::Pokemon pokemon = *(player->getPokemon());
            if(!(pokeRender->load(tileset2,sf::Vector2u(tileWidth,tileHeight),pokemon))) throw runtime_error("bad pokemon rendering");
            pokeVec.push_back(pokeRender);
        }

    }

}
