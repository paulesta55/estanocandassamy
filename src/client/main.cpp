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
    //create first state
    unique_ptr<State> state1;
    state1.reset(new State(Position(10,10), make_shared<Map>("res/src/etage3.json")));

    string name = "sala1";
    uint id = 1;
    shared_ptr<Salameche> sal = nullptr;
    sal.reset(new Salameche(id,"south",200,Position(10,10)));
    string playerName = "bob";
    state1->getPlayers().get()->push_back(new Player(false,playerName,id,sal));
    playerName = "tom";
    id++;
    state1->getPlayers()->push_back(new Player(true,playerName,id));


    //create 2nd state
    shared_ptr<State> state2;
    state2.reset(new State(Position(12,12),make_shared<Map>("res/src/etage2.json")));
    id++;
    shared_ptr<Carapuce> car = make_shared<Carapuce>(id,"north",200,Position(12,12));
    playerName = "Alice";
    state2->getPlayers()->push_back(new Player(false,playerName,id,car));


    //create 3rd state
    shared_ptr<State> state3;
    state3.reset(new State(Position(8,8),make_shared<Map>("res/src/etage1.json")));
//    id++;
    uint id3 = id+1;
    shared_ptr<Bulbizarre> bulbi = make_shared<Bulbizarre>(id3,"west",200,Position(8,8));
    string playerName2 = "Bernard";

    state3->getPlayers()->push_back(new Player(false,playerName2,id3,bulbi));
    if(argc == 2){
        if(!strcmp(argv[1],"state")){
            int success = 0;
            int fails = 0;
            // working case
            if(MapTest::testMap("res/src/etage1.json")){
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


    Scene* scene1 = new Scene(make_shared<State>(*state1),"res/src/tilemap2.png");

    scene1->draw();
    scene1->updateState(state2);
    scene1->draw();
    delete scene1;

    Scene* scene2 = new Scene(state2,"res/src/tilemap2.png");
    scene2->draw();
    delete scene2;

    Scene* scene3 = new Scene(state3,"res/src/tilemap2.png");
    scene3->draw();
    delete scene3;

    return 0;
}
