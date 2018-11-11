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
void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#undef NDEBUG

using namespace std;
using namespace state;
using namespace render;
using namespace engine;


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
        if(!strcmp(argv[1],"render"))
        {
            Engine engine;
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(make_shared<engine::Engine>(engine),"res/src/tilemap2.png",1));
            engine.getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(620,620),"test window");
            scene3->draw(window);

//            cout << "command built" <<endl;
            engine.addCommand(new MoveCommand(SOUTH, 0),0);
//            cout << "command added" <<endl;
            engine.runCommands();
//            cout << "command run" << endl;
//            cout << "command built" <<endl;
            scene3->draw(window);

//            delete command;
//            auto command2 = new MoveCommand(SOUTH,1);
            engine.addCommand(new MoveCommand(SOUTH,1),0);
//            cout << "command added" <<endl;
            engine.runCommands();
//            cout << "command run" << endl;

            scene3->draw(window);

            engine.addCommand(new MoveCommand(SOUTH,1),0);
//            cout << "command added" <<endl;
            engine.runCommands();
//            cout << "command run" << endl;

            scene3->draw(window);

            //            scene3.reset();

        }
        if(!strcmp(argv[1],"engine"))
        {
            cout << "engine" <<endl;
            shared_ptr<Engine> engine = make_shared<Engine>(State(Position(),make_shared<Map>("res/src/etage1.json")));
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(engine,"res/src/tilemap2.png",0));
            engine->getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(620,620),"test window");
            scene3->draw(window);

        }
        if(!strcmp(argv[1],"random_ai"))
        {
            cout << "random ai" <<endl;

        }

    }
    else {
        cout << "I don't understand"<< endl;
        cout << "you can only say hello" << endl;
    }




    return 0;
}
