//
// Created by paul on 1/5/19.
//
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "state.h"
#include "engine.h"
#include "ai.h"
#include "server.h"
using namespace ai;
using namespace std;
using namespace engine;
using namespace state;
using namespace server;

unsigned int findEnemy(map<unsigned int, shared_ptr<Player>> &MPlayers, unsigned int &player) {
    for (auto p:MPlayers) {
        if (p.first != player) {
            return p.first;
        }
    }
    new runtime_error("no enemy found");
    return static_cast<unsigned int>(-1);
}

int main(int argc, char *argv[]) {
    if(!strcmp(argv[1], "record")) {
        cout << "record" << endl;
        Server s;
        s.run();
    }

    return 0;
}
