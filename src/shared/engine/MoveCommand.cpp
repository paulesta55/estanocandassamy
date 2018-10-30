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

    cout << "begin movecommand" <<endl;
    State& state_ref = state;
    unique_ptr<Player> player_ptr;
    unique_ptr<Pokemon> poke_ptr;
    for( auto player : state_ref.getPlayers())
    {
        if(player.second->getID()== idPlayer)
        {
            player_ptr.reset(player.second);
        }
    }

    if(!player_ptr.get())
    {
        cout <<"no player"<<endl;
        throw new runtime_error("move command with bad player");
    }
    if(!player_ptr->getPokemon().get())
    {
        cout << "no pokemon" <<endl;
       throw new runtime_error("move command with bad pokemon");
    }

    cout << "player and poke found" <<endl;
    poke_ptr.reset(player_ptr->getPokemon().get());

    cout << "poke ptr built" <<endl;
    if(orientation == poke_ptr->orientation)
    {
        Position p = poke_ptr->getPosition();

        switch(orientation) {
            case Orientation ::SOUTH:

                p.y++;
                cout << "south +1"<< endl;
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
        poke_ptr->setPosition(p);
        cout << "set new position"<<endl;
        TabEvent tabEvent(TabEventId::MOVE,idPlayer);
        cout << "tab event built "<<endl;
        state_ref.notifyObservers(tabEvent);
    }
    else
    {
        poke_ptr->setOrientation(orientation);
        TabEvent tabEvent(TabEventId::MOVE,idPlayer);
        state_ref.notifyObservers(tabEvent);
    }


}

