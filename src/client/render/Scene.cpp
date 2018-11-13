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
#include "ai.h"
#include "engine.h"

using namespace std;
using namespace render;
using namespace state;
using namespace engine;
using namespace ai;
Scene::Scene(shared_ptr<engine::Engine> engine,string tileSet,unsigned int  pokeTarId) : pokeTarId(pokeTarId), engine(engine){


    this->tileset= std::move(tileSet);
    string tileset2 = "res/src/tilestPokemon.png";
    this->pokeTileSet.reset(new sf::Texture());
    this->pokeTileSet->loadFromFile("res/src/tilestPokemon.png");
    uint tileWidth = this->engine ->getState().getMap()->getTileWidth();
    uint tileHeight = this->engine->getState().getMap()->getTileHeight();
    tileSize = sf::Vector2u(tileWidth,tileHeight);

    updateMap();
    updatePlayers();


}

void Scene::draw(sf::RenderWindow& window) {

    //good dimensions : 620 x 620

    unique_ptr<AI> ai;
    ai.reset(new RandomAI);
//    int count = 300;
    while(window.isOpen()){
//        cout << "window opened" <<endl;
        // handle events
        sf::Event event;
        if(engine->getState().isGameFinished()) window.close();
        for(auto player: engine->getState().getPlayers())
        {
            if(!(player.second->getIA()) && !(player.second->getPokemon()->getAlive()))
            {
                cout << "GAME OVER" << endl;
                window.close();
            }
        }
        while (window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed :
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    sf::Keyboard::Key k = event.key.code;
                    switch(k){
                        case sf::Keyboard::Key::Right  :
                            engine->addCommand(new MoveCommand(EST,pokeTarId),0);
                            break;
                        case sf::Keyboard::Key::Left :
                            engine->addCommand(new MoveCommand(WEST,pokeTarId),0);
                            break;
                        case sf::Keyboard::Key::Up:
                            engine->addCommand(new MoveCommand(NORTH,pokeTarId),0);
                            break;
                        case sf::Keyboard::Key::Down:
                            engine->addCommand(new MoveCommand(SOUTH,pokeTarId),0);
                            break;
                        case sf::Keyboard::Key::A :
                            engine->addCommand(new AttackCommand(pokeTarId),0);
                            break;
                        case sf::Keyboard::Key::H:
                            engine->addCommand(new HealCommand(this->pokeTarId),0);
                            break;
                    }
                    for(auto player : engine->getState().getPlayers())
                    {
                        if(player.second->getIA() && player.second->getPokemon()->getAlive())
                            ai->run(*engine,player.first);
                    }
                    engine->runCommands();
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


        sf::View view2(sf::Vector2f(this->xCenter, this->yCenter), sf::Vector2f(200.f, 200.f));
        infoPlayers = "";
        int c = 0;
        for(auto player : engine->getState().getPlayers())
        {
            infoPlayers += "pokemon "+to_string(c)+" current life : "+
                           to_string(player.second->getPokemon()->getCurrentLife()) + "/"+ to_string(player.second->getPokemon()->getFullLife())+"\n";
            c++;
        }

        sf::Text text;
        text.setString(infoPlayers);
        text.setPosition(xCenter-90,yCenter-90);
        text.setFont(f);
        text.setColor(sf::Color::White);
        text.setCharacterSize(30);
        text.setScale(sf::Vector2f(0.27,0.27));
        text.setStyle(sf::Text::Regular);


        sf::Text t2;
        t2.setString("Use: 'L' to change the level\n'A' to attack\n'Arrow Keys' to move\n'H' to heal");
        t2.setPosition(xCenter,yCenter+40);
        t2.setFont(f);
        t2.setColor(sf::Color::Red);
        t2.setCharacterSize(25);
        t2.setScale(sf::Vector2f(0.27,0.27));
        t2.setStyle(sf::Text::Bold);

        window.draw(text);
        window.draw(t2);
//        count--;
        window.setView(view2);
        window.display();
    }
}

void Scene::updateMap() {
    layerVec.clear();

    if(!engine->getState().getMap())
    {
        throw new runtime_error("cannot render a state with no map");
    }
    uint tileWidth = engine ->getState().getMap()->getTileWidth();
    uint tileHeight = engine->getState().getMap()->getTileHeight();

    this->xCenter = engine->getState().getPlayers().at(pokeTarId)->getPokemon()->getPosition().x*tileWidth;
    this->yCenter = engine->getState().getPlayers().at(pokeTarId)->getPokemon()->getPosition().y*tileHeight;

    for(auto layer: *(engine->getState().getMap()->getLayers()))
    {
        shared_ptr<LayerRender> layerRend;
        layerRend.reset(new LayerRender());

        if(!(layerRend->load(this->tileset,sf::Vector2u(tileWidth,tileHeight),
                             layer.getData(),layer.getWidth(),layer.getHeight()))) throw  runtime_error("bad layer rendering");
        layerVec.push_back(layerRend);
    }
    string tileset2 = "res/src/tilestPokemon.png";
}

void movePokeRender(unsigned int pokeId)
{

}


void Scene::stateChanged(const state::Event& e) {
switch(e.getEventType())
{
    case TAB_EVENT:
        cout << "tab event" << endl;
        updatePlayers();
        break;
    case STATE_EVENT:
        StateEvent event = *(StateEvent*)(e.clone());
        switch(event.stateEvent)
        {
            case ATTACK:
                break;
            case StateEventId::LEVEL_CHANGE :
                updateMap();
                updatePlayers();
                break;
            case ALL_CHANGED:
                updateMap();
                updatePlayers();
                break;
        }
        break;

}

}

void Scene::updatePlayers() {
    this->pokeVec.clear();
    if(engine->getState().getPlayers().size() <=0){
        throw new runtime_error("cannot render a state with no players");
    }
    this->xCenter = engine->getState().getPlayers().at(pokeTarId)->getPokemon()->getPosition().x*tileSize.x;
    this->yCenter = engine->getState().getPlayers().at(pokeTarId)->getPokemon()->getPosition().y*tileSize.y;
    for( auto player :engine->getState().getPlayers())
    {
        shared_ptr<sf::Sprite> pokeRender;

        if(player.second->getPokemon()->getAlive()){
            pokeRender.reset(new sf::Sprite());
            pokeRender->setTexture(*pokeTileSet);
            std::shared_ptr<state::Pokemon> pokemon = player.second->getPokemon();
            unsigned int tileNumber = 0;
            switch (pokemon->getType()) {
                case PokeType ::BULBIZARRE://bulbizarre
                    tileNumber = 12;
                    break;
                case PokeType ::SALAMECHE://salameche
                    tileNumber = 33;
                    break;
                case CARAPUCE://carapuce
                    tileNumber = 54;
                    break;
                default:
                    throw new runtime_error("pokemon rendering error");
                    break;

            }
            Position position = pokemon->getPosition();
            tileNumber += pokemon->orientation;

            int tu = tileNumber % (pokeTileSet->getSize().x / tileSize.x);
            int tv = tileNumber / (pokeTileSet->getSize().x / tileSize.x);
            pokeRender->setTextureRect(sf::IntRect(tu * (tileSize.x+1)+1,tv * (tileSize.y+1)+1,tileSize.x,tileSize.y));
            pokeRender->setPosition(position.x* tileSize.x,position.y*tileSize.y);
            pokeVec.insert(make_pair(player.second->getID(),pokeRender));
        }

    }
}
