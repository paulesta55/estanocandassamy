#include <utility>

#include <utility>


//
// Created by paul on 22/10/18.
//

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "render.h"
#include <iostream>
#include <string>
#include <state/TabEvent.h>
#include "state.h"
#include "ai.h"
#include "engine.h"

using namespace std;
using namespace render;
using namespace state;
using namespace engine;
using namespace ai;
Scene::Scene(shared_ptr<engine::Engine> engine,string tileSet,unsigned int  pokeTarId) : engine(
        std::move(engine)),playerTarId(pokeTarId) {


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

    if (this->engine->getState().menu) {
        sf::Event event1;
        while (window.pollEvent(event1)) {
            switch (event1.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
                case sf::Event::KeyPressed:
                    sf::Keyboard::Key k1 = event1.key.code;
                    switch(k1) {
                        default:
                            break;
                        case sf::Keyboard::Return:
                            this->engine->getState().menu = false;
                            break;
                    }
                    break;
            }
        }
        sf::Texture texture;
        texture.loadFromFile("res/src/pokemonentryscene.png");
        sf::Sprite s;
        s.setPosition(0,0);
        s.setTexture(texture);
        sf::View v(sf::Vector2f(100,100),sf::Vector2f(200.f, 200.f));
        window.draw(s);
        window.setView(v);
        window.display();
    } else if(engine->getState().isGameFinished()) {
            if(engine->getState().gameWon) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    switch (event.type) {
                        case sf::Event::Closed:
                            window.close();
                            break;
                        default:
                            break;
                        case sf::Event::KeyPressed:
                            sf::Keyboard::Key k1 = event.key.code;
                            switch(k1) {
                                default:
                                    break;
                                case sf::Keyboard::Return:
                                    window.close();
                                    break;
                            }
                            break;
                    }
                }
                sf::Texture texture;
                texture.loadFromFile("res/src/pokemonfinalscene.png");
                sf::Sprite s;
                s.setPosition(0,0);
                s.setTexture(texture);
                sf::View v(sf::Vector2f(100,100),sf::Vector2f(200.f, 200.f));
                window.draw(s);
                window.setView(v);
                window.display();
            }
            else {
                sf::Event event;
                while (window.pollEvent(event)) {
                    switch (event.type) {
                        case sf::Event::Closed:
                            window.close();
                            break;
                        default:
                            break;
                        case sf::Event::KeyPressed:
                            sf::Keyboard::Key k1 = event.key.code;
                            switch(k1) {
                                default:
                                    break;
                                case sf::Keyboard::Return:
                                    window.close();
                                    break;
                            }
                            break;
                    }
                }
                sf::Texture texture;
                texture.loadFromFile("res/src/pokemongameoverscene.png");
                sf::Sprite s;
                s.setPosition(0,0);
                s.setTexture(texture);
                sf::View v(sf::Vector2f(100,100),sf::Vector2f(200.f, 200.f));
                window.draw(s);
                window.setView(v);
                window.display();
            }
        }
        else {


    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            default:
                break;
            case sf::Event::Closed :
                window.close();
                break;
            case sf::Event::KeyPressed:
                sf::Keyboard::Key k = event.key.code;
                switch (k) {
                    case sf::Keyboard::Key::Right  :
                        engine->addCommand(make_shared<MoveCommand>(EST, playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::Left :
                        engine->addCommand(make_shared<MoveCommand>(WEST, playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::Up:
                        engine->addCommand(make_shared<MoveCommand>(NORTH, playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::Down:
                        engine->addCommand(make_shared<MoveCommand>(SOUTH, playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::A :
                        engine->addCommand(make_shared<AttackCommand>(playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::H:
                        engine->addCommand(make_shared<HealCommand>(playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::R:
                        engine->undoCommands();
                    break;
                    default:
                        break;
                }


        }
        if (event.type == sf::Event::Closed)
            window.close();

    }


    window.clear();
    for (const auto &layerRend : layerVec) {
        window.draw(*layerRend);
    }
    for (auto pokeRend: pokeVec) {

        window.draw(*(pokeRend.second));
    }

    sf::Font f;
    if (!f.loadFromFile("res/src/arial.ttf")) {
        throw new runtime_error("cannot load font");
    }


    sf::View view2(sf::Vector2f(this->xCenter, this->yCenter), sf::Vector2f(200.f, 200.f));

    infoPlayers = "";
    int c = 0;
    for (auto player : engine->getState().getPlayers()) {
        if(player.second && player.second->getPokemon()) {

            infoPlayers += "pokemon " + to_string(c) + " current life : " +
                           to_string(player.second->getPokemon()->getCurrentLife()) + "/" +
                           to_string(player.second->getPokemon()->getFullLife()) + "\n";
            c++;
        }
    }

    sf::Text text;
    text.setString(infoPlayers);
    text.setPosition(xCenter - 90, yCenter - 90);
    text.setFont(f);
    text.setColor(sf::Color::White);
    text.setCharacterSize(30);
    text.setScale(sf::Vector2f(0.27, 0.27));
    text.setStyle(sf::Text::Regular);


    sf::Text t2;
    t2.setString("Use: 'A' to attack\n'Arrow Keys' to move\n'H' to heal");
    t2.setPosition(xCenter, yCenter + 40);
    t2.setFont(f);
    t2.setColor(sf::Color::Red);
    t2.setCharacterSize(25);
    t2.setScale(sf::Vector2f(0.27, 0.27));
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

//    this->xCenter = engine->getState().getPlayers().at(0)->getPokemon()->getPosition().x*tileWidth;
//    this->yCenter = engine->getState().getPlayers().at(0)->getPokemon()->getPosition().y*tileHeight;

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
//    const Event& event1 = e;

    if(e.getEventType()==TAB_EVENT) {
        cout << "tab event" << endl;
        unique_ptr<state::Event> eventTab(((TabEvent*)e.clone()));

        switch(((TabEvent*)eventTab.get())->tabEventId) {
            case MOVE:
                this->pokeVec[((TabEvent*)eventTab.get())->playerId]->setPosition(engine->getState().getPlayers().at(((TabEvent*)eventTab.get())->playerId)->getPokemon()->
                        getPosition().x*24,engine->getState().getPlayers().at(((TabEvent*)eventTab.get())->playerId)->getPokemon()->getPosition().y*24);
                this->xCenter = engine->getState().getPlayers().at(playerTarId)->getPokemon()->getPosition().x*tileSize.x;
                this->yCenter = engine->getState().getPlayers().at(playerTarId)->getPokemon()->getPosition().y*tileSize.y;
                break;
            case DEATH:
                pokeVec.erase(((TabEvent*)eventTab.get())->playerId);
                updatePlayers();
                break;
            case ORIENT:
                updatePlayers();
                break;
        }

    }
    else
    { unique_ptr<StateEvent> event((StateEvent*)(e.clone()));
        switch(event->stateEvent)
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
            default:
                break;
        }
    }

}


void Scene::updatePlayers() {
    this->pokeVec.clear();
    if(engine->getState().getPlayers().size() <1){
        throw new runtime_error("cannot render a state with no players");
    }
    this->xCenter = engine->getState().getPlayers()[playerTarId]->getPokemon()->getPosition().x*tileSize.x;
    this->yCenter = engine->getState().getPlayers()[playerTarId]->getPokemon()->getPosition().y*tileSize.y;
    for( auto player :engine->getState().getPlayers())
    {
        shared_ptr<sf::Sprite> pokeRender;

        if(player.second && player.second->getPokemon()->getAlive()){
            pokeRender.reset(new sf::Sprite());
            pokeRender->setTexture(*(pokeTileSet.get()));
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
                    throw runtime_error("pokemon rendering error");

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
