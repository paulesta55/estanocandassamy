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

        if(checkMove(p,state_ref))
        {
            player_ptr->getPokemon()->setPosition(p);
//        cout << "set new position"<<endl;
            TabEvent tabEvent(TabEventId::MOVE,idPlayer);
//        cout << "tab event built "<<endl;
            state_ref.notifyObservers(tabEvent);
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

bool MoveCommand::checkMove(Position& p,State& state)
{
    unsigned int nextTile = state.getMap()->getLayers()->at(0).getData()->at(p.x+p.y*state.getMap()->getWidth());
    if(nextTile!=35)
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
