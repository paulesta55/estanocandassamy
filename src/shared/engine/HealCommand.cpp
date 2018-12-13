//
// Created by paul on 28/10/18.
//
#include <state/StateEventId.h>
#include "HealCommand.h"
#include "state.h"
#include "engine.h"

using namespace state;
using namespace std;
using namespace engine;

engine::HealCommand::HealCommand(unsigned int id) {
    idPlayer = id;}

std::shared_ptr<PreviousState>  engine::HealCommand::execute(state::State &state) {
    for(auto player : state.getPlayers())
    {
        if(player.second->getID() == idPlayer && player.second->getPokemon()->getAlive())
        {
            if(player.second->getPokemon().get()){
            auto prevStat = make_shared<PreviousState>(player.second->getPokemon()->getOrientation(),idPlayer,player.second->getPokemon()->getPosition(),player.second->getPokemon()->getCurrentLife(),ACTION_HEAL);

                unsigned int fullLife = player.second->getPokemon()->getFullLife();
                unsigned int curLife =player.second->getPokemon()->getCurrentLife();
                if(curLife+20<fullLife)
                {
                    curLife+=20;
                    player.second->getPokemon()->setCurrentLife(curLife);
                }
                else {
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
    return nullptr;
}
