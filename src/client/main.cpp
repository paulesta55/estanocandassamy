#include <iostream>
#include "string.h"
#include <unistd.h>
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
#include <thread>
#include <mutex>
sf::Clock clock1;
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

void handleInputs(shared_ptr<Engine> engine, sf::Window &window, unsigned int playerTarId) {

    if (engine->getState().menu) {
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
                    switch (k1) {
                        default:
                            break;
                        case sf::Keyboard::Return:
                            engine->getState().menu = false;
                            break;
                    }
                    break;
            }
        }
    } else if (engine->getState().isGameFinished()) {
        if (engine->getState().gameWon) {
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
                        switch (k1) {
                            default:
                                break;
                            case sf::Keyboard::Return:
                                window.close();
                                break;
                        }
                        break;
                }
            }
        } else {
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
                        switch (k1) {
                            default:
                                break;
                            case sf::Keyboard::Return:
                                window.close();
                                break;
                        }
                        break;
                }
            }
        }
    } else {

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
                    if(clock1.getElapsedTime().asMilliseconds()>110) {
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
                        clock1.restart();
                    }
                    break;



            }
            if (event.type == sf::Event::Closed)
                window.close();

        }
    }
}

unsigned int findEnemy(map<unsigned int, shared_ptr<Player>> &MPlayers, unsigned int &player) {
    for (auto p:MPlayers) {
        if (p.first != player) {
            return p.first;
        }
    }
    new runtime_error("no enemy found");
    return -1;
}

//new commit
int main(int argc, char *argv[]) {
//    Map m("res/src/etage1.json");

    if (argc == 2) {
        if (strcmp(argv[1], "hello") == 0) {
            cout << "Bonjour le monde !" << endl;
        }
        if (!strcmp(argv[1], "state")) {
            Map m("res/src/etage1.json");
            cout << m.getWidth() << endl;
            int success = 0;
            int fails = 0;

            // working case
            if (MapTest::testMap("res/src/etage1.json")) {
                success++;
                cout << "working case test success" << endl;
            } else {
                fails++;
                cerr << "working case test fails" << endl;
            }

            // test map.json extension
            if (!MapTest::testMap("res/test/test.txt")) {
                success++;
                cout << "json extension test success" << endl;
            } else {
                fails++;
                cerr << "json extension test fails" << endl;
            }

            // test map format
            if (!MapTest::testMap("res/test/mapformattest.json")) {
                success++;
                cout << "map format test success" << endl;
            } else {
                fails++;
                cerr << "map format test fails" << endl;
            }

            // test layers format
            if (!MapTest::testMap("res/test/layerdatatest.json")) {
                success++;
                cout << "layer data test success" << endl;
            } else {
                fails++;
                cerr << "layer data test fails" << endl;
            }

            // test layers dimension
            if (!MapTest::testMap("res/test/layerdimensionstest.json")) {
                success++;
                cout << "layer dimensions test success" << endl;
            } else {
                fails++;
                cerr << "layer dimensions test fails" << endl;
            }


            cout << success << " tests success out of " << success + fails << endl;
            cout << fails << " tests fails out of " << success + fails << endl;

        }
        if (!strcmp(argv[1], "render")) {

            shared_ptr<mutex> m = make_shared<mutex>();
            shared_ptr<mutex> m_exec = make_shared<mutex>();
            // Create our engine
            shared_ptr<Engine> engine = make_shared<Engine>(m,
                                                            State(Position(), make_shared<Map>("res/src/etage1.json")));

            // Create some players
            const unsigned int id = 1;
            unsigned int idPlayer1 = 1;
            string player = "Alice";
            const pair<const unsigned int, shared_ptr<Player>> pair1 = make_pair(id, make_shared<Player>(true, player,
                                                                                                         idPlayer1,
                                                                                                         make_shared<Bulbizarre>(
                                                                                                                 WEST,
                                                                                                                 200,
                                                                                                                 Position(
                                                                                                                         3,
                                                                                                                         9))));
            engine->getState().getPlayers().insert(pair1);
            const unsigned int id2 = 0;
            unsigned int idPlayer2 = 0;
            string player2 = "Bob";
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2,
                                                                                 make_shared<Player>(false, player2,
                                                                                                     idPlayer2,
                                                                                                     make_shared<Salameche>(
                                                                                                             EST, 150,
                                                                                                             Position(
                                                                                                                     20,
                                                                                                                     20))));
            engine->getState().getPlayers().insert(pair2);
            engine->getState().center = Position(7, 7);

            // Set up the render
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(engine, "res/src/tilemap2.png", 0));
            engine->getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(600, 600), "test window");

            while (window.isOpen()) {

                handleInputs(engine, window, 0);

                scene3->draw(window);
            }


        }
        if (!strcmp(argv[1], "engine")) {
            cout << "engine" << endl;
            shared_ptr<mutex> m = make_shared<mutex>();
            shared_ptr<mutex> m_exec = make_shared<mutex>();
            // Create our engine
            shared_ptr<Engine> engine = make_shared<Engine>(m,
                                                            State(Position(), make_shared<Map>("res/src/etage1.json")));

            // Create some players
            const unsigned int id = 1;
            unsigned int idPlayer1 = 1;
            string player = "Alice";
            const pair<const unsigned int, shared_ptr<Player>> pair1 = make_pair(id, make_shared<Player>(true, player,
                                                                                                         idPlayer1,
                                                                                                         make_shared<Bulbizarre>(
                                                                                                                 WEST,
                                                                                                                 200,
                                                                                                                 Position(
                                                                                                                         3,
                                                                                                                         9))));
            engine->getState().getPlayers().insert(pair1);
            const unsigned int id2 = 0;
            unsigned int idPlayer2 = 0;
            string player2 = "Bob";
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2,
                                                                                 make_shared<Player>(false, player2,
                                                                                                     idPlayer2,
                                                                                                     make_shared<Salameche>(
                                                                                                             EST, 150,
                                                                                                             Position(
                                                                                                                     20,
                                                                                                                     20))));
            engine->getState().getPlayers().insert(pair2);
            engine->getState().center = Position(7, 7);

            // Set up the render
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(engine, "res/src/tilemap2.png", 0));
            engine->getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(600, 600), "test window");

            while (window.isOpen()) {
//        cout << "window opened" <<endl;

                // Manage user inputs
                handleInputs(engine, window, 0);

                scene3->draw(window);

                engine->runCommands();
            }


        }

        if (!strcmp(argv[1], "random_ai")) {
            cout << "random ai" << endl;
            shared_ptr<mutex> m = make_shared<mutex>();
            shared_ptr<mutex> m_exec = make_shared<mutex>();
            // Create our engine
            shared_ptr<Engine> engine = make_shared<Engine>(m,
                                                            State(Position(), make_shared<Map>("res/src/etage1.json")));

            // Create some players
            const unsigned int id = 1;
            unsigned int idPlayer1 = 1;
            string player = "Alice";
            const pair<const unsigned int, shared_ptr<Player>> pair1 = make_pair(id, make_shared<Player>(true, player,
                                                                                                         idPlayer1,
                                                                                                         make_shared<Bulbizarre>(
                                                                                                                 WEST,
                                                                                                                 200,
                                                                                                                 Position(
                                                                                                                         3,
                                                                                                                         9))));
            engine->getState().getPlayers().insert(pair1);
            const unsigned int id2 = 0;
            unsigned int idPlayer2 = 0;
            string player2 = "Bob";
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2,
                                                                                 make_shared<Player>(false, player2,
                                                                                                     idPlayer2,
                                                                                                     make_shared<Salameche>(
                                                                                                             EST, 150,
                                                                                                             Position(
                                                                                                                     20,
                                                                                                                     20))));
            engine->getState().getPlayers().insert(pair2);
            engine->getState().center = Position(7, 7);

            // Set up the render
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(engine, "res/src/tilemap2.png", 0));
            engine->getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(600, 600), "test window");


            unique_ptr<AI> ai;
            ai.reset(new RandomAI);
            while (window.isOpen()) {
                // Manage user inputs
                handleInputs(engine, window, 0);

                scene3->draw(window);
                if (engine->getCommands().size() > 0) {
                    for (auto player : engine->getState().getPlayers()) {
                        if (player.second && player.second->getIA() && player.second->getPokemon()->getAlive()) {
                            cout << "run ai" << endl;
                            ai->run(*engine, player.first, 0);
                            break;
                        }
                    }
                    engine->runCommands();
                }
            }

        }
        if (!strcmp(argv[1], "heuristic_ai")) {
            shared_ptr<mutex> m = make_shared<mutex>();
            shared_ptr<mutex> m_exec = make_shared<mutex>();
            // Create our engine
            shared_ptr<Engine> engine = make_shared<Engine>(m,
                                                            State(Position(), make_shared<Map>("res/src/etage1.json")));

            // Create some players
            const unsigned int id = 1;
            unsigned int idPlayer1 = 1;
            string player = "Alice";
            const pair<const unsigned int, shared_ptr<Player>> pair1 = make_pair(id, make_shared<Player>(true, player,
                                                                                                         idPlayer1,
                                                                                                         make_shared<Bulbizarre>(
                                                                                                                 WEST,
                                                                                                                 200,
                                                                                                                 Position(
                                                                                                                         3,
                                                                                                                         9))));
            engine->getState().getPlayers().insert(pair1);
            const unsigned int id2 = 0;
            unsigned int idPlayer2 = 0;
            string player2 = "Bob";
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2,
                                                                                 make_shared<Player>(false, player2,
                                                                                                     idPlayer2,
                                                                                                     make_shared<Salameche>(
                                                                                                             EST, 150,
                                                                                                             Position(
                                                                                                                     20,
                                                                                                                     20))));
            engine->getState().getPlayers().insert(pair2);
            engine->getState().center = Position(7, 7);

            // Set up the render
            shared_ptr<Scene> scene3;
            scene3.reset(new Scene(engine, "res/src/tilemap2.png", 0));
            engine->getState().registerObserver(scene3.get());
            sf::RenderWindow window(sf::VideoMode(600, 600), "test window");

            // Call our AI computer
            unique_ptr<AI> ai;
            ai.reset(new HeuristicAI);

            while (window.isOpen()) {

                // Manage user inputs
                handleInputs(engine, window, 0);
                // Look for real living players
                scene3->draw(window);
                if (!engine->getCommands().empty()) {
                    for (auto player : engine->getState().getPlayers()) {
                        if (player.second && player.second->getIA() && player.second->getPokemon()->getAlive()) {
                            cerr << "run ai" << endl;
                            ai->run(*engine, player.first, 0);
                            break;
                        }
                    }
                    engine->runCommands();
                }
            }

        }

    }
    if (!strcmp(argv[1], "rollback")) {
        cout << "ROLLBACK" << endl;
        shared_ptr<mutex> m = make_shared<mutex>();
        shared_ptr<mutex> m_exec = make_shared<mutex>();
        // Create our engine
        shared_ptr<Engine> engine = make_shared<Engine>(m, State(Position(), make_shared<Map>("res/src/etage1.json")));

        // Create some AI players
        const unsigned int id = 1;
        unsigned int idPlayer1 = 1;
        string player = "Alice";
        const pair<const unsigned int, shared_ptr<Player>> pair1 = make_pair(id, make_shared<Player>(true, player,
                                                                                                     idPlayer1,
                                                                                                     make_shared<Bulbizarre>(
                                                                                                             WEST, 200,
                                                                                                             Position(5,
                                                                                                                      20))));
        engine->getState().getPlayers().insert(pair1);
        const unsigned int id2 = 0;
        unsigned int idPlayer2 = 0;
        string player2 = "Bob";
        const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2, make_shared<Player>(true, player2,
                                                                                                      idPlayer2,
                                                                                                      make_shared<Salameche>(
                                                                                                              EST, 150,
                                                                                                              Position(
                                                                                                                      20,
                                                                                                                      20))));
        engine->getState().getPlayers().insert(pair2);
        engine->getState().center = Position(7, 7);

        // Set up the render
        shared_ptr<Scene> scene3;
        scene3.reset(new Scene(engine, "res/src/tilemap2.png", 0));
        engine->getState().registerObserver(scene3.get());
        sf::RenderWindow window(sf::VideoMode(600, 600), "test window");

        // Call our AI computer
        unique_ptr<AI> aiTest;
        aiTest.reset(new HeuristicAI);

        aiTest->restrictArea = false;
        int count = 1;
        while (window.isOpen()) {

            scene3->draw(window);
            if (!(engine->getState().menu)) {
                if (count < 60) {
                    count++;
                    unique_ptr<unsigned int> enemyId;
                    for (auto player : engine->getState().getPlayers()) {
                        if (player.second && player.second->getIA() && player.second->getPokemon()->getAlive()) {
                            cerr << "run ai" << endl;
                            unsigned int pId = player.first;
                            enemyId.reset(new unsigned int(findEnemy(engine->getState().getPlayers(), pId)));
                            aiTest->run(*engine, player.first, *enemyId);
                        }
                    }
                    if (!(engine->getCommands().empty())) usleep(1000000);
                    engine->runCommands();

                } else if (count >= 60 && count <= 180) {
                    engine->undoCommands();
                    count++;
                    usleep(500000);
                } else {
                    window.close();
                }
                cout << "count :" << count << endl;
            }


        }
    }
    if (!strcmp(argv[1], "deep_ai")) {
        cout << "DEEP AI" << endl;
        shared_ptr<mutex> m = make_shared<mutex>();
        shared_ptr<Engine> engine = make_shared<Engine>(m, State(Position(), make_shared<Map>("res/src/etage1.json")));

        // Create some AI players
        const unsigned int id = 1;
        unsigned int idPlayer1 = 1;
        string player = "Alice";
        const pair<const unsigned int, shared_ptr<Player>> pair1 = make_pair(id, make_shared<Player>(true, player,
                                                                                                     idPlayer1,
                                                                                                     make_shared<Bulbizarre>(
                                                                                                             WEST, 200,
                                                                                                             Position(3,
                                                                                                                      9))));
        engine->getState().getPlayers().insert(pair1);
        const unsigned int id2 = 0;
        unsigned int idPlayer2 = 0;
        string player2 = "Bob";
        const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2, make_shared<Player>(false, player2,
                                                                                                      idPlayer2,
                                                                                                      make_shared<Salameche>(
                                                                                                              EST, 150,
                                                                                                              Position(
                                                                                                                      20,
                                                                                                                      20))));
        engine->getState().getPlayers().insert(pair2);
        engine->getState().center = Position(7, 7);

        // Set up the render
        shared_ptr<Scene> scene3;
        scene3.reset(new Scene(engine, "res/src/tilemap2.png", 0));
        engine->getState().registerObserver(scene3.get());
        sf::RenderWindow window(sf::VideoMode(600, 600), "test window");

        // Call our AI computer
        unique_ptr<AI> aiTest;
        aiTest.reset(new DeepAI);


        while (window.isOpen()) {
            handleInputs(engine, window, 0);
            scene3->draw(window);
            if (!engine->getCommands().empty()) {
                for (auto player : engine->getState().getPlayers()) {
                    if (player.second && player.second->getIA() && player.second->getPokemon()->getAlive()) {
                        cerr << "run ai" << endl;
                        aiTest->run(*engine, player.first, 0);

                        break;
                    }
                }
                engine->runCommands();
            }
        }

    }
    if (!strcmp(argv[1], "threads")) {
        cout << "threads" << endl;


        shared_ptr<mutex> m = make_shared<mutex>();
        shared_ptr<Engine> engine = make_shared<Engine>(m, State(Position(), make_shared<Map>("res/src/etage1.json")));

        // Create some AI players
        const unsigned int id = 1;
        unsigned int idPlayer1 = 1;
        string player = "Alice";
        const pair<const unsigned int, shared_ptr<Player>> pair1 = make_pair(id, make_shared<Player>(true, player,
                                                                                                     idPlayer1,
                                                                                                     make_shared<Bulbizarre>(
                                                                                                             WEST, 200,
                                                                                                             Position(3,
                                                                                                                      9))));
        engine->getState().getPlayers().insert(pair1);
        const unsigned int id2 = 0;
        unsigned int idPlayer2 = 0;
        string player2 = "Bob";
        const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2, make_shared<Player>(false, player2,
                                                                                                      idPlayer2,
                                                                                                      make_shared<Salameche>(
                                                                                                              EST, 150,
                                                                                                              Position(
                                                                                                                      20,
                                                                                                                      20))));
        engine->getState().getPlayers().insert(pair2);
        engine->getState().center = Position(7, 7);

        // Set up the render
        shared_ptr<Scene> scene3;
        scene3.reset(new Scene(engine, "res/src/tilemap2.png", 0));
        engine->getState().registerObserver(scene3.get());


        // Call our AI computer
        shared_ptr<AI> aiTest;
        aiTest.reset(new HeuristicAI);
        aiTest->restrictArea = false;
        cerr << "render running" << endl;
        sf::RenderWindow window(sf::VideoMode(600, 600), "test window");
        while (window.isOpen()) {
            thread eng([engine, aiTest, m] {
                cerr << "engine running" << endl;
                unique_ptr<unsigned int> enemyId;
                if (!(engine->getState().menu) && !(engine->getCommands().empty())) {
                    for (auto player : engine->getState().getPlayers()) {
                        if (player.second && player.second->getIA() && player.second->getPokemon()->getAlive()) {
                            cerr << "run ai" << endl;
                            unsigned int pId = player.first;
                            enemyId.reset(new unsigned int(findEnemy(engine->getState().getPlayers(), pId)));
                            aiTest->run(*engine, player.first, *enemyId);

                        }
                    }
                    cout << "about to sleep" << endl;
                    //usleep(1000000);
                    engine->runCommands();
                    cout << "end commands" <<endl;
                }

            });
            //thread render([engine,scene3] {

            handleInputs(engine, window, 0);

            scene3->draw(window);

            eng.join();
        }


    } else {
        cout << "I don't understand" << endl;
        cout << "you can only say hello" << endl;
    }


    return 0;
}
