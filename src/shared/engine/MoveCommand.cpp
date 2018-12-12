//
// Created by paul on 28/10/18.
//

#include <iostream>
#include <state/TabEventId.h>
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

std::shared_ptr<PreviousState> MoveCommand::execute(state::State &state) {

    cout << "begin movecommand" <<endl;
    State& state_ref = state;
    shared_ptr<Player> player_ptr = nullptr;
//    unique_ptr<Pokemon> poke_ptr;
//    for( auto player : state_ref.getPlayers())
//    {
//        if(player.second->getID()== idPlayer)
//        {
//            player_ptr = player.second;
//            cout << "player found" <<endl;
//        }
//    }


    player_ptr = state.getPlayers()[idPlayer];

    auto prevStat = make_shared<PreviousState>(state.getPlayers()[idPlayer]->getPokemon()->getOrientation(),idPlayer,state.getPlayers()[idPlayer]->getPokemon()->getPosition(),state.getPlayers()[idPlayer]->getPokemon()->getCurrentLife(),ACTION_MV);


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
                    shared_ptr<Map> newMap;
                    mapPath+=to_string(state_ref.getEpoch()+1);
                    mapPath+=".json";
                    string newName = "IA "+std::to_string(new_epoch);
                    unsigned int new_id = new_epoch+1;
                    Position new_position;

                    switch(new_epoch)
                    {
                        case 1:

                            newMap.reset(new Map(mapPath));
                            state_ref.setMap(newMap);
                            new_id = 2;
                            new_position = Position(13,5);
//                            state.getPlayers().erase(1);

                            state_ref.getPlayers().insert(make_pair(new_id,make_shared<Player>(true,newName,new_id,make_shared<Carapuce>(EST,200,Position(4,4)))));
                            state_ref.getPlayers()[idPlayer]->getPokemon()->setPosition(new_position);
                            break;

                        case 2:

                            newMap.reset(new Map(mapPath));
                            state_ref.setMap(newMap);
                            new_id = 3;
                            new_position = Position(21,3);
                            state_ref.getPlayers().insert(make_pair(new_id,make_shared<Player>(true,newName,new_id,make_shared<Carapuce>(EST,200,Position(3,21)))));
                            state_ref.getPlayers()[idPlayer]->getPokemon()->setPosition(new_position);
                            break;
                        case 3:
                            state_ref.setGameFinished(true);
                            state_ref.gameWon = true;
                            cout << "GAME WON!!!" << endl;
                            break;

                    }

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
        TabEvent tabEvent(TabEventId::ORIENT,idPlayer);
        state_ref.notifyObservers(tabEvent);
    }

    return prevStat;

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
        if(player.second->getID()!=this->idPlayer && player.second->getPokemon()->getPosition().x == p.x &&
        player.second->getPokemon()->getPosition().y == p.y && player.second->getPokemon()->getAlive())
        {
            return false;
        }

    }
//    cout << "next tile: " << nextTile << endl;
    return true;
}
