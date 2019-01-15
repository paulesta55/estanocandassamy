//
// Created by paul on 1/8/19.
//

#include "Client.h"
#include "client.h"
#include "render.h"
#include "state.h"
#include "ai.h"
#include "engine.h"
#include <iostream>
#include <thread>
#include <zconf.h>
#include <SFML/Network.hpp>

using namespace render;
using namespace engine;
using namespace std;
using namespace state;
using namespace ai;

//unsigned int findEnemy(std::map<unsigned int, std::shared_ptr<state::Player>> &MPlayers, unsigned int &player) {
//    for (auto p:MPlayers) {
//        if (p.first != player) {
//            return p.first;
//        }
//    }
//    new runtime_error("no enemy found");
//    return -1;
//}

void client::Client::run()
{

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

    engine->getState().menu = false;

    // Call our AI computer
    ai->restrictArea = false;
    cerr << "render running" << endl;
    sf::RenderWindow window(sf::VideoMode(600, 600), "thread window");
    shared_ptr<Engine> enginePtr = engine;
    shared_ptr<AI> aiPtr = ai;
    thread eng([this] {
        while (1)
        {
            cerr << "engine running" << endl;
            unique_ptr<unsigned int> enemyId;
            //if (!(engine->getState().menu) && !(engine->getCommands().empty())) {
            for (auto player : engine->getState().getPlayers())
            {
                if (player.second && player.second->getIA() && player.second->getPokemon()->getAlive())
                {
                    cerr << "run ai" << endl;
                    unsigned int pId = player.first;
                    enemyId.reset(new unsigned int(this->findEnemy(engine->getState().getPlayers(), pId)));
                    ai->run(*engine, player.first, *enemyId);
                }
            }
            cout << "about to sleep" << endl;
            usleep(1000000);
            engine->runCommands(false);
            //}
            cout << "end commands" << endl;
            if (engine->getState().isGameFinished())
                return 0;
        }

        //  }
    });
    while (window.isOpen())
    {

        handleInputs(enginePtr, window, 0);

        scene3->draw(window);
    }
    eng.join();
}

void client::Client::connectNetwork()
{
    this->addPlayer(0, 1, 100, 1, 1);
    int id = 1;
    int lock = 1;
    while (lock == 1)
    {
        lock = this->getPlayer(id);
        id += 1;
    }
    this->addPlayer(0, 1, 100, 1, 1);
}

int client::Client::connectAsFirst()
{
    int idPlayer = this->addPlayer(0, 2, 200, 3, 9);
    const unsigned int id1 = idPlayer;
    unsigned int idPlayer1 = idPlayer;
    localPlayerId = idPlayer;
    string player = "Alice";
    const pair<const unsigned int, shared_ptr<Player>> pair1 = make_pair(id1, make_shared<Player>(false, player,
                                                                                                  idPlayer1,
                                                                                                  make_shared<Bulbizarre>(
                                                                                                      WEST, 200,
                                                                                                      Position(3,
                                                                                                               9))));
    engine->getState().getPlayers().insert(pair1);

    int idEnnemi = 2;
    int test = this->getPlayer(0);
    while (test != 2)
    {
        test = this->getPlayer(0);
        cout << "waiting" << endl;
        usleep(10000);
    }

    cout << "ready to start" << endl;
    std::vector<int> statsEnnemi = this->getPlayerStats(idEnnemi);
    if (!statsEnnemi.empty())
    {
        const unsigned int id2 = idEnnemi;
        unsigned int idPlayer2 = idEnnemi;
        string player2 = "Bob";
        if (statsEnnemi[0] == 0)
        {
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2, make_shared<Player>(false, player2,
                                                                                                          idPlayer2,
                                                                                                          make_shared<Bulbizarre>(
                                                                                                              static_cast<state::Orientation>(statsEnnemi[1]), statsEnnemi[2],
                                                                                                              Position(
                                                                                                                  statsEnnemi[3],
                                                                                                                  statsEnnemi[4]))));
            engine->getState().getPlayers().insert(pair2);
        }
        else if (statsEnnemi[0] == 1)
        {
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2, make_shared<Player>(false, player2,
                                                                                                          idPlayer2,
                                                                                                          make_shared<Salameche>(
                                                                                                              static_cast<state::Orientation>(statsEnnemi[1]), statsEnnemi[2],
                                                                                                              Position(
                                                                                                                  statsEnnemi[3],
                                                                                                                  statsEnnemi[4]))));
            engine->getState().getPlayers().insert(pair2);
        }
        else
        {
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2, make_shared<Player>(false, player2,
                                                                                                          idPlayer2,
                                                                                                          make_shared<Carapuce>(
                                                                                                              static_cast<state::Orientation>(statsEnnemi[1]), statsEnnemi[2],
                                                                                                              Position(
                                                                                                                  statsEnnemi[3],
                                                                                                                  statsEnnemi[4]))));
            engine->getState().getPlayers().insert(pair2);
        }

        engine->getState().center = Position(7, 7);

        shared_ptr<Scene> scene4;
        scene4.reset(new Scene(engine, "res/src/tilemap2.png", idPlayer));
        engine->getState().registerObserver(scene4.get());

        engine->getState().menu = false;

        cerr << "render running" << endl;
        sf::RenderWindow window(sf::VideoMode(600, 600), "thread window");
        shared_ptr<Engine> enginePtr = engine;
//         thread eng([this] {
//             while (1)
//             {
//                 if(this->tour%2 == 0) {
//                     this->getCommand();
//                     engine->runCommands();
//                 }
//                 cerr << "engine running" << endl;
//                 unique_ptr<unsigned int> enemyId;
//                 cout << "about to sleep" << endl;
//                 usleep(1000000);
//                 engine->runCommands(false);
//                 //}
//                 cout << "end commands" << endl;
//                 if (engine->getState().isGameFinished())
//                     return 0;
//             }

             //  }
//         });
        while (window.isOpen())
        {

            handleInputs(enginePtr, window, 0);

            scene4->draw(window);
        }
        // eng.join();
    }
    else
    {
        cout << "Error can't acces network" << endl;
    }

    return 0;
}

int client::Client::connectAsSecond()
{
    int idPlayer = this->addPlayer(1, 3, 150, 20, 20);
    const unsigned int id1 = idPlayer;
    unsigned int idPlayer1 = idPlayer;
    localPlayerId = idPlayer;
    cout << this->getPlayer(0) << endl;
    int idEnnemi = 1;
    string player = "Bob";
    const pair<const unsigned int, shared_ptr<Player>> pair1 = make_pair(id1, make_shared<Player>(false, player,
                                                                                                  idPlayer1,
                                                                                                  make_shared<Salameche>(
                                                                                                      EST, 150,
                                                                                                      Position(20,
                                                                                                               20))));
    engine->getState().getPlayers().insert(pair1);                                                                                               

    cout << "ready to start" << endl;

    std::vector<int> statsEnnemi = this->getPlayerStats(idEnnemi);
    if (!statsEnnemi.empty())
    {
        const unsigned int id2 = idEnnemi;
        unsigned int idPlayer2 = idEnnemi;
        string player2 = "Bob";
        if (statsEnnemi[0] == 0)
        {
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2, make_shared<Player>(false, player2,
                                                                                                          idPlayer2,
                                                                                                          make_shared<Bulbizarre>(
                                                                                                              static_cast<state::Orientation>(statsEnnemi[1]), statsEnnemi[2],
                                                                                                              Position(
                                                                                                                  statsEnnemi[3],
                                                                                                                  statsEnnemi[4]))));
            engine->getState().getPlayers().insert(pair2);
        }
        else if (statsEnnemi[0] == 1)
        {
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2, make_shared<Player>(false, player2,
                                                                                                          idPlayer2,
                                                                                                          make_shared<Salameche>(
                                                                                                              static_cast<state::Orientation>(statsEnnemi[1]), statsEnnemi[2],
                                                                                                              Position(
                                                                                                                  statsEnnemi[3],
                                                                                                                  statsEnnemi[4]))));
            engine->getState().getPlayers().insert(pair2);
        }
        else
        {
            const pair<const unsigned int, shared_ptr<Player>> pair2 = make_pair(id2, make_shared<Player>(false, player2,
                                                                                                          idPlayer2,
                                                                                                          make_shared<Carapuce>(
                                                                                                              static_cast<state::Orientation>(statsEnnemi[1]), statsEnnemi[2],
                                                                                                              Position(
                                                                                                                  statsEnnemi[3],
                                                                                                                  statsEnnemi[4]))));
            engine->getState().getPlayers().insert(pair2);
        }
        engine->getState().center = Position(7, 7);

        shared_ptr<Scene> scene3;
        scene3.reset(new Scene(engine, "res/src/tilemap2.png", idPlayer));
        engine->getState().registerObserver(scene3.get());

        engine->getState().menu = false;

        cerr << "render running" << endl;
        sf::RenderWindow window(sf::VideoMode(600, 600), "thread window");
        shared_ptr<Engine> enginePtr = engine;
//         thread eng([this] {
//             while (1)
//             {
//                 cerr << "engine running" << endl;
//                 unique_ptr<unsigned int> enemyId;
//                 cout << "about to sleep" << endl;
//                 usleep(1000000);
//                 engine->runCommands(false);
//                 //}
//                 cout << "end commands" << endl;
//                 if (engine->getState().isGameFinished())
//                     return 0;
//             }
//
//             //  }
//         });
        while (window.isOpen())
        {

            handleInputs(enginePtr, window, 0);

            scene3->draw(window);
        }
        // eng.join();
    }
    else
    {
        cout << "Error can't acces network" << endl;
    }

    return 0;
}

int client::Client::connect()
{
    int nbPlayer = this->getPlayer(0);
    cout << nbPlayer << endl;
    if (nbPlayer == 1)
    {
        this->connectAsSecond();
    }
    else if (nbPlayer == 0)
    {
        this->connectAsFirst();
    }
    else
    {
        cout << "No more connections possible" << endl;
    }
    return 0;
}

void client::Client::deletePlayer(int id)
{
    sf::Http http("http://localhost", 8080);
    sf::Http::Response response;
    sf::Http::Request req3;
    req3.setMethod(sf::Http::Request::Delete);
    req3.setHttpVersion(1, 1);
    req3.setUri("/user/" + std::to_string(id));
    req3.setField("Content-Type", "application/json");
    req3.setBody("");
    response = http.sendRequest(req3);
}

int client::Client::addPlayer(int idPoke, int orientation, int currentLife, int x, int y)
{
    sf::Http http("http://localhost", 8080);
    sf::Http::Response response;
    sf::Http::Request req3;
    Json::Value User;
    User["idPoke"] = idPoke;
    User["orientation"] = orientation;
    User["currentLife"] = currentLife;
    User["x"] = x;
    User["y"] = y;
    req3.setUri("/user");
    req3.setMethod(sf::Http::Request::Put);
    req3.setBody(User.toStyledString());
    req3.setField("Content-Type", "application/json");
    req3.setHttpVersion(1, 1);
    response = http.sendRequest(req3);
    if (response.getStatus() == sf::Http::Response::Created)
    {
        //cout<< response.getBody()<<endl;
        //Get This player Id
        Json::Value root;
        Json::Value players;
        Json::Reader reader;
        if (!reader.parse(response.getBody(), root, false))
        {
            cout << reader.getFormattedErrorMessages() << endl;
        }
        int id = root["id"].asInt();
        if (id == -1)
        {
            cout << "No more connections possible" << endl;
            return -1;
        }
        else
        {
            return id;
        }
    }
    else
    {
        cout << "Put Request Failed: " << response.getStatus() << endl;
        return -1;
    }
}

int client::Client::getPlayer(int id)
{
    sf::Http http("http://localhost", 8080);
    sf::Http::Response response;
    sf::Http::Request req("/user/" + to_string(id), sf::Http::Request::Get);
    response = http.sendRequest(req);

    if (response.getStatus() == sf::Http::Response::Ok)
    {
        Json::Value root;
        Json::Value players;
        Json::Reader reader;
        if (!reader.parse(response.getBody(), root, false))
        {
            cout << reader.getFormattedErrorMessages() << endl;
        }
        if (id == 0)
        {
            int nbPlayer = root["status"].asInt();
            cout << response.getBody() << endl;
            return nbPlayer;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

std::vector<int> client::Client::getPlayerStats(int id)
{
    sf::Http http("http://localhost", 8080);
    sf::Http::Response response;
    sf::Http::Request req("/user/" + to_string(id), sf::Http::Request::Get);
    response = http.sendRequest(req);
    std::vector<int> stats;
    if (response.getStatus() == sf::Http::Response::Ok)
    {
        Json::Value root;
        Json::Value players;
        Json::Reader reader;
        if (!reader.parse(response.getBody(), root, false))
        {
            cout << reader.getFormattedErrorMessages() << endl;
        }
        stats.push_back(root["idPoke"].asInt());
        stats.push_back(root["orientation"].asInt());
        stats.push_back(root["currentLife"].asInt());
        stats.push_back(root["x"].asInt());
        stats.push_back(root["y"].asInt());
        return stats;
    }
    else
    {
        return stats;
    }
}

void client::Client::handleInputs(std::shared_ptr<Engine> engine, sf::Window &window, unsigned int playerTarId)
{

    if (engine->getState().menu)
    {
        sf::Event event1;
        while (window.pollEvent(event1))
        {
            switch (event1.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            case sf::Event::KeyPressed:
                sf::Keyboard::Key k1 = event1.key.code;
                switch (k1)
                {
                default:
                    break;
                case sf::Keyboard::Return:
                    engine->getState().menu = false;
                    break;
                }
                break;
            }
        }
    }
    else if (engine->getState().isGameFinished())
    {
        if (engine->getState().gameWon)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
                case sf::Event::KeyPressed:
                    sf::Keyboard::Key k1 = event.key.code;
                    switch (k1)
                    {
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
        else
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
                case sf::Event::KeyPressed:
                    sf::Keyboard::Key k1 = event.key.code;
                    switch (k1)
                    {
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
    }
    else
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            default:
                break;
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:

                sf::Keyboard::Key k = event.key.code;
                if (clock1.getElapsedTime().asMilliseconds() > 110)
                {
                    switch (k)
                    {
                    case sf::Keyboard::Key::Right:
                        engine->addCommand(make_shared<MoveCommand>(EST, playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::Left:
                        engine->addCommand(make_shared<MoveCommand>(WEST, playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::Up:
                        engine->addCommand(make_shared<MoveCommand>(NORTH, playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::Down:
                        engine->addCommand(make_shared<MoveCommand>(SOUTH, playerTarId), playerTarId);
                        break;
                    case sf::Keyboard::Key::A:
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

unsigned int
client::Client::findEnemy(std::map<unsigned int, std::shared_ptr<state::Player>> &MPlayers, unsigned int &player)
{
    for (auto p : MPlayers)
    {
        if (p.first != player)
        {
            return p.first;
        }
    }
    new runtime_error("no enemy found");
    return -1;
}

client::Client::Client()
{
    engine = make_shared<Engine>(State(Position(), make_shared<Map>("res/src/etage1.json")));
}

void client::Client::getCommand() {
    sf::Http http("http://localhost", 8080);
    sf::Http::Response response;
    sf::Http::Request req("/command/" + localPlayerId, sf::Http::Request::Get);
    response = http.sendRequest(req);
    std::vector<int> stats;
    if (response.getStatus() == sf::Http::Response::Ok)
    {
        Json::Value root;
        Json::Value players;
        Json::Reader reader;
        if (!reader.parse(response.getBody(), root, false))
        {
            cout << reader.getFormattedErrorMessages() << endl;
        }
        stats.push_back(root["idPoke"].asInt());
        stats.push_back(root["orientation"].asInt());
        stats.push_back(root["currentLife"].asInt());
        stats.push_back(root["x"].asInt());
        stats.push_back(root["y"].asInt());
       return;
    }
    else
    {
        return;
    }
}
