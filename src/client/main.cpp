#include <iostream>
#include <string.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include "state.h"
#include "render.h"
#include "MapTest.h"
#include <cassert>
void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#undef NDEBUG

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[])
{
    unique_ptr<State> state1;
    state1.reset(new State(make_shared<Map>("res/src/map3.json")));

    string name = "sala1";
    uint id = 1;
    shared_ptr<Salameche> sal = nullptr;
    sal.reset(new Salameche("south",id));
    string playerName = "bob";
    state1->getPlayers().get()->push_back(new Player(false,playerName,id,sal));
    playerName = "tom";
    id++;
    state1->getPlayers()->push_back(new Player(true,playerName,id));
    cout << state1->getMap()->getTileSet()->getSource() << endl;
    string tileset = "res/src/"+state1->getMap()->getTileSet()->getSource();

    string tileset2 = "res/src/poketile.json";
//    ResManager resManager(tileset);
//    cout << state1->getPlayers()->at(0)->getName() << endl;
//    cout << state1->getPlayers()->at(1)->getName() << endl;

    if(argc == 2){
        if(!strcmp(argv[1],"state")){
            int success = 0;
            int fails = 0;
            // working case
            if(MapTest::testMap("res/src/map.json")){
                success++;
                cout << "working case test success" <<endl;
            }else{
                fails++;
                cerr << "working case test failes" << endl;
            }

            // test map.json extension
            if(!MapTest::testMap("res/test/test.txt")){
                success++;
                cout << "json extension test success" << endl;
            }else{
                fails++;
                cerr << "json extension test failes" << endl;
            }

            // test map format
            if(!MapTest::testMap("res/test/mapformattest.json")){
                success++;
                cout << "map format test success" <<endl;
            }else{
                fails++;
                cerr << "map format test failes" << endl;
            }

            // test layers format
            if(!MapTest::testMap("res/test/layerdatatest.json")){
                success++;
                cout << "layer data test success" <<endl;
            }else{
                fails++;
                cerr << "layer data test failes" << endl;
            }

            // test layers dimension
            if(!MapTest::testMap("res/test/layerdimensionstest.json")){
                success++;
                cout << "layer dimensions test success" <<endl;
            }else{
                fails++;
                cerr << "layer dimensions test failes" << endl;
            }


            cout << success << " tests success out of " << success + fails << endl;
            cout << fails << " tests fails out of " << success + fails << endl;

        }
    }


    // check the number of arguments
    if(argc == 2) {
        // check the 1st argument
        if(strcmp(argv[1],"hello")== 0) {
            cout << "Bonjour le monde !" << endl;
        }
        // display a warning when a wrong number of arguments is given

    }
    else {
        cout << "I don't understand"<< endl;
        cout << "you can only say hello" << endl;
    }

//    uint width = state1->getMap()->getHeight();
//    uint height = state1->getMap()->getWidth();
//    sf::RenderWindow window(sf::VideoMode(720,720),"test window");
//
//    ResManager* pokeManager = new ResManager(tileset2);
//    pokeManager->init();
//    LayerRender map;
//    if (!map.load("res/src/tilemap.png", sf::Vector2u(24, 24), state1->getMap()->getLayers()->at(0).getData(),
//            width,height))
//        return -1;
//    LayerRender map2;
//    if(!map2.load("res/src/tilemap.png",sf::Vector2u(24,24),state1->getMap()->getLayers()->at(1).getData(),width,height))
//        return -1;
//    // run the main loop
//    while (window.isOpen())
//    {
//        // handle events
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if(event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        unique_ptr<sf::Sprite> pokeSprite;
//        pokeSprite.reset(new sf::Sprite());
//        pokeSprite->setTexture(pokeManager->textureCache->at(33));
//        pokeSprite->setPosition(24*10,24*10);
//
//        unique_ptr<sf::Sprite> pokeSprite2;
//        pokeSprite2.reset(new sf::Sprite());
//        pokeSprite2->setTexture(pokeManager->textureCache->at(54));
//        pokeSprite2->setPosition(window.getView().getCenter());
//
//        // draw the map
//        window.clear();
//        window.draw(map);
//        window.draw(map2);
//        window.draw(*pokeSprite);
//        window.draw(*pokeSprite2);
//        window.display();
//    }
//    delete pokeManager;


Scene Scene(make_shared<State>(*state1),"res/src/tilemap.png");
    return 0;
}
