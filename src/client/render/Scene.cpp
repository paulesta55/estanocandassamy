#include <utility>


//
// Created by paul on 22/10/18.
//

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "render.h"
#include <iostream>
#include <string>
#include "state.h"

#include "engine.h"

using namespace std;
using namespace render;
using namespace state;
using namespace engine;
Scene::Scene(shared_ptr<engine::Engine> engine,string tileSet,unsigned int  pokeTarId) : pokeTarId(pokeTarId), engine(engine){


//    vector<shared_ptr<LayerRender>> layerVec;
//cout<<"enter scene" <<endl;
    this->tileset= std::move(tileSet);
    string tileset2 = "res/src/tilestPokemon.png";
    this->pokeTileSet.reset(new sf::Texture());
    this->pokeTileSet->loadFromFile("res/src/tilestPokemon.png");
//    cout << "tileset loaded" <<endl;
//    state->registerObserver(this);
//    cout << "observer register" <<endl;
    this->updateState();
//    cout << "update state "<<endl;


}

void Scene::draw(sf::RenderWindow& window) {

    //good dimensions : 620 x 620

    int count = 300;
    while(count>0 && window.isOpen()){
//        cout << "window opened" <<endl;
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
        for(const auto &layerRend : layerVec)
        {
            window.draw(*layerRend);
        }
        for(auto pokeRend: pokeVec)
        {

            window.draw(*(pokeRend.second));
        }

        sf::Font f;
        if(!f.loadFromFile("res/src/arial.ttf")){
            throw new runtime_error("cannot load font");
        }


        // good size : 200 x 200
//       window.draw(text);
        sf::View view2(sf::Vector2f(this->xCenter, this->yCenter), sf::Vector2f(200.f, 200.f));
        infoPlayers = "";
        for(auto player : engine->getState().getPlayers())
        {
            infoPlayers += "pokemon "+to_string(player.second->getPokemon()->getID())+" current life : "+
                           to_string(player.second->getPokemon()->getCurrentLife()) + "/"+ to_string(player.second->getPokemon()->getFullLife())+"\n";
        }

        sf::Text text;
        text.setString(infoPlayers);
//        cout << infoPlayers << endl;
        text.setPosition(xCenter-90,yCenter-90);
        text.setFont(f);
        text.setColor(sf::Color::Black);
        text.setCharacterSize(30);
        text.setScale(sf::Vector2f(0.27,0.27));
        text.setStyle(sf::Text::Regular);


        window.draw(text);
        count--;
        window.setView(view2);
        window.display();
    }
}

void Scene::updateState() {

    pokeVec.clear();
    layerVec.clear();
    if(engine->getState().getPlayers().size() <=0){
        throw new runtime_error("cannot render a state with no players");
    }
    if(!engine->getState().getMap())
    {
        throw new runtime_error("cannot render a state with no map");
    }
//    cout << "layer vec cleared" <<endl;
    uint tileWidth = engine ->getState().getMap()->getTileWidth();
    uint tileHeight = engine->getState().getMap()->getTileHeight();

//    cout << "tilewidth and tileheight ok" <<endl;
    this->xCenter = engine->getState().getPlayers().at(pokeTarId)->getPokemon()->getPosition().x*tileWidth;
    this->yCenter = engine->getState().getPlayers().at(pokeTarId)->getPokemon()->getPosition().y*tileHeight;

//    cout <<"center ok" <<endl;
    for(auto layer: *(engine->getState().getMap()->getLayers()))
    {
        shared_ptr<LayerRender> layerRend;
        layerRend.reset(new LayerRender());

        if(!(layerRend->load(this->tileset,sf::Vector2u(tileWidth,tileHeight),
                             layer.getData(),layer.getWidth(),layer.getHeight()))) throw  runtime_error("bad layer rendering");
        layerVec.push_back(layerRend);
    }
//    cout <<"layers ok"<<endl;
    string tileset2 = "res/src/tilestPokemon.png";
//    vector<shared_ptr<PokeRender>> layerPoke;



//    t.setScale(0.1,0.1);

    for( auto player :engine->getState().getPlayers())
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
//    pokeVec.at(0)->setPosition(Position(this->state->getPlayers().at(0)->getPokemon()->getPosition().x-1,this->state->getPlayers().at(0)->getPokemon()->getPosition().y-1));
}

void movePokeRender(unsigned int pokeId)
{

}


void Scene::stateChanged(const state::Event& e) {
    cout << "state changes"<<endl;
//    if(e.getEventType() == TAB_EVENT )
//    {
//        state::TabEvent event = *(TabEvent*)(e.clone());
//        cout<<"event cloned"<<endl;
//        switch(event.tabEventId) {
//            case MOVE:
//                pokeVec.at(event.playerId)->setPosition();
//                cout << "pokerender moved" <<endl;
//                break;
//
//        }
//    }
//    cout << "out of state changed switch"<<endl;
    this->updateState();
}


