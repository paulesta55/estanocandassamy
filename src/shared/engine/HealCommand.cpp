//
// Created by paul on 28/10/18.
//
#include <state/StateEventId.h>
#include "HealCommand.h"
#include "state.h"

using namespace state;
using namespace std;

engine::HealCommand::HealCommand(unsigned int id) {
    idPlayer = id;}

void engine::HealCommand::execute(state::State &state) {
    for(auto player : state.getPlayers())
    {
        if(player.second->getID() == idPlayer)
        {
            if(player.second->getPokemon().get()){
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
                StateEvent e(StateEventId::ALL_CHANGED);
                state.notifyObservers(e);
            }
            else
                {
                throw new std::runtime_error("non existing pokemon for heal command");
            }

            break;
        }

    }
}
