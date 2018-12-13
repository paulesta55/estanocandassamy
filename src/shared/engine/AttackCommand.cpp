//
// Created by paul on 28/10/18.
//
#include "AttackCommand.h"
#include "state.h"
#include <memory>
#include <iostream>
#include <engine.h>

using namespace engine;
using namespace std;
using namespace state;



std::shared_ptr<PreviousState> AttackCommand::execute(state::State &state) {
    State& state_ref = state;
    shared_ptr<Player> player_ptr = nullptr;
//    unique_ptr<Pokemon> poke_ptr;
    player_ptr=state_ref.getPlayers()[this->idPlayer];


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

    Position p(player_ptr->getPokemon()->getPosition());
    unsigned int id_attacked = this->idPlayer;
    shared_ptr<PreviousState> prevStat(new PreviousState(state_ref.getPlayers().at(id_attacked)->getPokemon()->
    getOrientation(),id_attacked,state_ref.getPlayers().at(id_attacked)->getPokemon()->getPosition(),
    state_ref.getPlayers().at(id_attacked)->getPokemon()->getCurrentLife(),ACTION_ATT));

    switch(player_ptr->getPokemon()->getOrientation())
    {
        case EST:

            p.x++;
           id_attacked = this->findPokemon(p,state_ref);
            if(id_attacked != this->idPlayer)
            {
                unsigned int lifeAttacked = state_ref.getPlayers().at(id_attacked)->getPokemon()->getCurrentLife();
                unsigned int newLife = 0;
                if(lifeAttacked > 30)
                {
                    newLife = lifeAttacked - 30;
                }
                state_ref.getPlayers().at(id_attacked)->getPokemon()->setCurrentLife(newLife);
                if(newLife==0) {
                    state_ref.getPlayers()[id_attacked]->getPokemon()->setAlive(false);
                    TabEvent event(TabEventId::DEATH,id_attacked);
                    state_ref.notifyObservers(event);
                }
                else {
                    StateEvent e(StateEventId::ATTACK);
                    state_ref.notifyObservers(e);
                }

            }
            return prevStat;
            break;

        case SOUTH:
            p.y++;
             id_attacked = this->findPokemon(p,state_ref);
            if(id_attacked != this->idPlayer)
            {
                unsigned int lifeAttacked = state_ref.getPlayers().at(id_attacked)->getPokemon()->getCurrentLife();
                unsigned int newLife = 0;
                if(lifeAttacked > 50)
                {
                    newLife = lifeAttacked - 50;
                }
                state_ref.getPlayers().at(id_attacked)->getPokemon()->setCurrentLife(newLife);
                if(newLife==0) {
                    state_ref.getPlayers()[id_attacked]->getPokemon()->setAlive(false);
                    TabEvent event(TabEventId::DEATH,idPlayer);
                    state_ref.notifyObservers(event);
                }
                else {
                    StateEvent e(StateEventId::ATTACK);
                    state_ref.notifyObservers(e);
                }
            }
            return prevStat;
            break;
        case NORTH:
            p.y--;
            id_attacked = this->findPokemon(p,state_ref);
            if(id_attacked != this->idPlayer)
            {
                unsigned int lifeAttacked = state_ref.getPlayers().at(id_attacked)->getPokemon()->getCurrentLife();
                unsigned int newLife = 0;
                if(lifeAttacked > 50)
                {
                    newLife = lifeAttacked - 50;
                }
                state_ref.getPlayers().at(id_attacked)->getPokemon()->setCurrentLife(newLife);
                if(newLife==0) {
                    state_ref.getPlayers()[id_attacked]->getPokemon()->setAlive(false);
                    TabEvent event(TabEventId::DEATH,idPlayer);
                    state_ref.notifyObservers(event);
                }
                else {
                    StateEvent e(StateEventId::ATTACK);
                    state_ref.notifyObservers(e);
                }
            }
            return prevStat;
            break;
        case WEST:
            p.x--;
            id_attacked = this->findPokemon(p,state_ref);
            if(id_attacked != this->idPlayer)
            {
                unsigned int lifeAttacked = state_ref.getPlayers().at(id_attacked)->getPokemon()->getCurrentLife();
                unsigned int newLife = 0;
                if(lifeAttacked > 50)
                {
                    newLife = lifeAttacked - 50;
                }
                state_ref.getPlayers().at(id_attacked)->getPokemon()->setCurrentLife(newLife);
                if(newLife==0) {
                    state_ref.getPlayers()[id_attacked]->getPokemon()->setAlive(false);
                    TabEvent event(TabEventId::DEATH,idPlayer);
                    state_ref.notifyObservers(event);
                }
                else {
                    StateEvent e(StateEventId::ATTACK);
                    state_ref.notifyObservers(e);
                }

            }
            return prevStat;
            break;


    }
    return nullptr;

}

AttackCommand::AttackCommand(unsigned int idPlayer) : idPlayer(idPlayer){
}


/**
 * @param p
 * @param state_ref
 * @return idPlayer if can't find a pokemon at p. PokeId at location p
 */
unsigned int AttackCommand::findPokemon(state::Position &p,State& state_ref) {

    for(auto entry: state_ref.getPlayers())
    {
        if(entry.second && entry.second->getID() != this->idPlayer)
        {
            if(entry.second->getPokemon()->getPosition().x == p.x && entry.second->getPokemon()->getPosition().y == p.y)
            {
                return entry.second->getID();
            }
        }
    }
    return this->idPlayer;
}

