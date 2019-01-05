//
// Created by paul on 28/10/18.
//
#include <state/StateEventId.h>
#include "HealCommand.h"
#include "state.h"
#include "engine.h"
#include <iostream>
#include <fstream>

using namespace state;
using namespace std;
using namespace engine;

engine::HealCommand::HealCommand(unsigned int id)
{
    idPlayer = id;
    // ofstream file;
    // file.open("Hello.txt", ios_base::app);
    // file << "\"commands\":{" << endl;
    // file << "   \"idPlayer\": \"" << id <<"\"," << endl;
    // file << "   \"type\": \"HEAL\"" << endl;
    // file << "}" << endl;
    // file.close();
}

void HealCommand::serialize(Json::Value &root){
    Json::Value newCmd;

    newCmd["Command"]["CommandTypeId"] = 0;
    newCmd["Command"]["idPlayer"] = this->idPlayer;
    if(!(root["commands"].empty())) {
        root["commands"][root["commands"].size()] = newCmd;
    }
    else {
        root["commands"][0] = newCmd;
    }
}

std::shared_ptr<PreviousState> engine::HealCommand::execute(state::State &state)
{
    for (auto player : state.getPlayers())
    {
        if (player.second)
        {
            if (player.second->getID() == idPlayer && player.second->getPokemon()->getAlive())
            {
                if (player.second->getPokemon().get())
                {
                    auto prevStat = make_shared<PreviousState>(player.second->getPokemon()->getOrientation(), idPlayer, player.second->getPokemon()->getPosition(), player.second->getPokemon()->getCurrentLife(), ACTION_HEAL);
                    unsigned int fullLife = player.second->getPokemon()->getFullLife();
                    unsigned int curLife = player.second->getPokemon()->getCurrentLife();
                    if (curLife + 20 < fullLife)
                    {
                        curLife += 20;
                        player.second->getPokemon()->setCurrentLife(curLife);
                    }
                    else
                    {
                        player.second->getPokemon()->setCurrentLife(fullLife);
                    }
                    StateEvent e(StateEventId::ATTACK);
                    state.notifyObservers(e);
                    return prevStat;
                }
                else
                {
                    throw new std::runtime_error("non existing pokemon for heal command");
                }

                break;
            }
        }
    }
    return nullptr;
}
