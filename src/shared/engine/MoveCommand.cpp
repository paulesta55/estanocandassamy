//
// Created by paul on 28/10/18.
//

#include <iostream>
#include "MoveCommand.h"
#include "engine.h"
#include "state.h"
using namespace engine;
using namespace std;
using namespace state;

MoveCommand::MoveCommand(state::Orientation o, unsigned int id) {
    orientation = o;
    this->idPlayer = id;
}

void MoveCommand::execute(state::State &state) {

//    cout << "begin movecommand" <<endl;
    State& state_ref = state;
    shared_ptr<Player> player_ptr = nullptr;
//    unique_ptr<Pokemon> poke_ptr;
    for( auto player : state_ref.getPlayers())
    {
        if(player.second->getID()== idPlayer)
        {
            player_ptr = player.second;
//            cout << "player found" <<endl;
        }
    }


    if(!player_ptr)
    {
        cout <<"no player"<<endl;
        throw new runtime_error("move command with bad player");
    }
    if(!(player_ptr->getPokemon().get()))
    {
        cout << "no pokemon" <<endl;
       throw new runtime_error("move command with bad pokemon");
    }

//    cout << "player and poke found" <<endl;
//    player_ptr->getPokemon();

//    cout << "poke ptr built" <<endl;
    if(orientation == player_ptr->getPokemon()->orientation)
    {
        Position p = player_ptr->getPokemon()->getPosition();

        switch(orientation) {
            case Orientation ::SOUTH:
                p.y++;
                break;

            case Orientation ::NORTH:
                p.y--;
                break;
            case Orientation ::WEST:
                p.x--;
                break;
            case Orientation ::EST:
                p.x++;
                break;

        }
        unsigned int nextTile = state.getMap()->getLayers()->at(0).getData()->at(p.x+p.y*state.getMap()->getWidth());
        if(checkMove(p,state_ref,nextTile))
        {

//        cout << "set new position"<<endl;

            if(nextTile == 158)
            {
                bool changelevel = true;
                for(auto player:state_ref.getPlayers())
                {
                    if(player.second->getID()!=this->idPlayer &&  player.second->getPokemon()->getAlive())
                    {
                        changelevel = false;
                        break;
                    }

                }
                if(changelevel)
                {
                    player_ptr->getPokemon()->setPosition(p);
                    unsigned int new_epoch =state_ref.getEpoch()+1;
                    state_ref.setEpoch(new_epoch);
                    string  mapPath = "res/src/etage";
                    mapPath+=to_string(state_ref.getEpoch());
                    mapPath+=".json";
                    shared_ptr<Map> newMap;
                    newMap.reset(new Map(mapPath));
                    state_ref.setMap(newMap);
                    StateEvent stateEvent(StateEventId::LEVEL_CHANGE);
                    state_ref.notifyObservers(stateEvent);
                }

            }
            else
            {
                player_ptr->getPokemon()->setPosition(p);
                TabEvent tabEvent(TabEventId::MOVE,idPlayer);
                state_ref.notifyObservers(tabEvent);

            }
//        cout << "tab event built "<<endl;
        }


    }
    else
    {
        player_ptr->getPokemon()->setOrientation(orientation);
        TabEvent tabEvent(TabEventId::MOVE,idPlayer);
        state_ref.notifyObservers(tabEvent);
    }

//    cout << "end of move command" << endl;
}

bool MoveCommand::checkMove(Position& p,State& state, unsigned int nextTile)
{

    if(nextTile!=35 && nextTile!=158)
    {
        return false;
    }
    for(auto player : state.getPlayers())
    {
        if(player.second->getID()!=this->idPlayer && player.second->getPokemon()->getPosition().x == p.x && player.second->getPokemon()->getPosition().y == p.y && player.second->getPokemon()->getAlive())
        {
            return false;
        }

    }
    cout << "next tile: " << nextTile << endl;
    return true;
}
