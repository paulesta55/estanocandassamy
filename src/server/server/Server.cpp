//
// Created by paul on 1/9/19.
//

#include <iostream>
#include <memory>
#include <zconf.h>
#include "engine.h"
#include "ai.h"
#include "Server.h"
#include "state.h"

using namespace engine;
using namespace server;
using namespace state;
using namespace std;
using namespace ai;


void Server::run() {
    shared_ptr<Engine> engine = make_shared<Engine>( State(Position(), make_shared<Map>("res/src/etage1.json")),true);

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
    engine->getState().menu = false;

    // Call our AI computer
    shared_ptr<AI> aiTest;
    aiTest.reset(new HeuristicAI);
    aiTest->restrictArea = false;
    unsigned int count = 0;

    while(count < 60 ) {
        unique_ptr<unsigned int> enemyId;
        //if (!(engine->getState().menu) && !(engine->getCommands().empty())) {
        for (auto player : engine->getState().getPlayers()) {
            if (player.second && player.second->getIA() && player.second->getPokemon()->getAlive()) {
                cerr << "run ai" << endl;
                unsigned int pId = player.first;
                enemyId.reset(new unsigned int(findEnemy(engine->getState().getPlayers(), pId)));
                aiTest->run(*engine, player.first, *enemyId);

            }
        }
        usleep(1000000);
        engine->runCommands(false);
        //}
        cout << "epoch : " << count <<endl;
        count ++;
    }
}

unsigned int Server::findEnemy(std::map<unsigned int, std::shared_ptr<state::Player>> &MPlayers, unsigned int &player) {
    for (auto p:MPlayers) {
        if (p.first != player) {
            return p.first;
        }
    }
    new runtime_error("no enemy found");
    return -1;
}
