#include <iostream>
#include "string.h"

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include "state.h"
#include "render.h"
#include "MapTest.h"
#include "engine.h"
#include <cassert>
#include <memory>
#include <utility>
#include "engine.h"
#include "ai.h"
void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#undef NDEBUG

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

//new commit
int main(int argc,char* argv[])
{
//    Map m("res/src/etage1.json");

    if(argc == 2){
        if(strcmp(argv[1],"hello")== 0) {
            cout << "Bonjour le monde !" << endl;
        }
        if(!strcmp(argv[1],"state")){
            Map m("res/src/etage1.json");
            cout << m.getWidth() <<endl;
            int success = 0;
            int fails = 0;

            // working case
            if(MapTest::testMap("res/src/etage1.json")){
                success++;
                cout << "working case test success" <<endl;
            }else{
                fails++;
                cerr << "working case test fails" << endl;
            }

            // test map.json extension
            if(!MapTest::testMap("res/test/test.txt")){
                success++;
                cout << "json extension test success" << endl;
            }else{
                fails++;
                cerr << "json extension test fails" << endl;
            }

            // test map format
            if(!MapTest::testMap("res/test/mapformattest.json")){
                success++;
                cout << "map format test success" <<endl;
            }else{
                fails++;
                cerr << "map format test fails" << endl;
            }

            // test layers format
            if(!MapTest::testMap("res/test/layerdatatest.json")){
                success++;
                cout << "layer data test success" <<endl;
            }else{
                fails++;
                cerr << "layer data test fails" << endl;
            }

            // test layers dimension
            if(!MapTest::testMap("res/test/layerdimensionstest.json")){
                success++;
                cout << "layer dimensions test success" <<endl;
            }else{
                fails++;
                cerr << "layer dimensions test fails" << endl;
            }


            cout << success << " tests success out of " << success + fails << endl;
            cout << fails << " tests fails out of " << success + fails << endl;

        }
        if(!strcmp(argv[1],"render"))
        {

            shared_ptr<Engine> engine = make_shared<Engine>(State(Position(),make_shared<Map>("res/src/etage1.json")));
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(engine,"res/src/tilemap2.png",0));
            engine->getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(620,620),"test window");
            //good dimensions : 620 x 620

//            unique_ptr<AI> ai;
//            ai.reset(new RandomAI);
//    int count = 300;
            while(window.isOpen()) {
//        cout << "window opened" <<endl;
                // handle events

                if (engine->getState().isGameFinished()) window.close();
                for (auto player: engine->getState().getPlayers()) {
                    if (!(player.second->getIA()) && !(player.second->getPokemon()->getAlive())) {
                        cout << "GAME OVER" << endl;
                        window.close();
                    }
                }
                scene3->draw(window);
            }



        }
        if(!strcmp(argv[1],"engine"))
        {
            cout << "engine" <<endl;
            shared_ptr<Engine> engine = make_shared<Engine>(State(Position(),make_shared<Map>("res/src/etage1.json")));
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(engine,"res/src/tilemap2.png",0));
            engine->getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(620,620),"test window");
            //good dimensions : 620 x 620

//            unique_ptr<AI> ai;
//            ai.reset(new RandomAI);
//    int count = 300;
            while(window.isOpen()) {
//        cout << "window opened" <<endl;
                // handle events

                if (engine->getState().isGameFinished()) window.close();
                for (auto player: engine->getState().getPlayers()) {
                    if (!(player.second->getIA()) && !(player.second->getPokemon()->getAlive())) {
                        cout << "GAME OVER" << endl;
                        window.close();
                    }
                }
                scene3->draw(window);
//                if (engine->getCommands().size() > 0) {
//                    for (auto player : engine->getState().getPlayers()) {
//                        if (player.second->getIA() && player.second->getPokemon()->getAlive()) {
//                            cout << "run ai" << endl;
//                            ai->run(*engine, player.first);
//                            break;
//                        }
//                    }
                engine->runCommands();
            }


        }

        if(!strcmp(argv[1],"random_ai"))
        {
            cout << "random ai" <<endl;
            shared_ptr<Engine> engine = make_shared<Engine>(State(Position(),make_shared<Map>("res/src/etage1.json")));
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(engine,"res/src/tilemap2.png",0));
            engine->getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(720,720),"test window");
            //good dimensions : 620 x 620

            unique_ptr<AI> ai;
            ai.reset(new RandomAI);
//    int count = 300;
            while(window.isOpen()) {
//        cout << "window opened" <<endl;
                // handle events

                if (engine->getState().isGameFinished()) window.close();
                for (auto player: engine->getState().getPlayers()) {
                    if (!(player.second->getIA()) && !(player.second->getPokemon()->getAlive())) {
                        cout << "GAME OVER" << endl;
                        window.close();
                    }
                }
                scene3->draw(window);
                if (engine->getCommands().size() > 0) {
                    for (auto player : engine->getState().getPlayers()) {
                        if (player.second->getIA() && player.second->getPokemon()->getAlive()) {
                            cout << "run ai" << endl;
                            ai->run(*engine, player.first);
                            break;
                        }
                    }
                    engine->runCommands();
                }
            }

        }
        if(!strcmp(argv[1],"heuristic_ai"))
        {

            shared_ptr<Engine> engine = make_shared<Engine>(State(Position(),make_shared<Map>("res/src/etage1.json")));
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(engine,"res/src/tilemap2.png",0));
            engine->getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(600,600),"test window");

            unique_ptr<AI> ai;
            ai.reset(new HeuristicAI);

            while(window.isOpen()) {


                if (engine->getState().isGameFinished()) window.close();
                for (auto player: engine->getState().getPlayers()) {
                    if (!(player.second->getIA()) && !(player.second->getPokemon()->getAlive())) {
                        cout << "GAME OVER" << endl;
                        window.close();
                    }
                }
                scene3->draw(window);
                if (engine->getCommands().size() > 0) {
                    for (auto player : engine->getState().getPlayers()) {
                        if (player.second->getIA() && player.second->getPokemon()->getAlive()) {
                            cout << "run ai" << endl;
                            ai->run(*engine, player.first);
                            break;
                        }
                    }
                    engine->runCommands();
                }
            }

        }

    }
    else {
        cout << "I don't understand"<< endl;
        cout << "you can only say hello" << endl;
    }




    return 0;
}
