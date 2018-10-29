//
// Created by paul on 28/10/18.
//

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
        throw new runtime_error("move command with bad player");
    }
    if(!player_ptr->getPokemon().get())
    {
       throw new runtime_error("move command with bad pokemon");
    }

    poke_ptr.reset(player_ptr->getPokemon().get());

    if(orientation == poke_ptr->orientation)
    {
        Position p = poke_ptr->getPosition();

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
        poke_ptr->setPosition(p);
        TabEvent tabEvent(TabEventId::MOVE,idPlayer);
        state_ref.notifyObservers(tabEvent);
    }
    else
    {
        poke_ptr->setOrientation(orientation);
        TabEvent tabEvent(TabEventId::MOVE,idPlayer);
        state_ref.notifyObservers(tabEvent);
    }


}

