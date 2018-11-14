//
// Created by paul on 13/11/18.
//

#include "HeuristicAI.h"
#include "ai.h"
#include "engine.h"
#include "state.h"

using namespace engine;
using namespace ai;
using namespace state;
using namespace std;

void ai::HeuristicAI::run(engine::Engine &e, unsigned int player) {

    Position IAPos = e.getState().getPlayers()[player]->getPokemon()->getPosition();
    if (e.getState().getPlayers()[player]->getPokemon()->getCurrentLife() != e.getState().getPlayers()[player]
            ->getPokemon()->getFullLife()) {
        e.addCommand(new HealCommand(player), 1);

        return;
    }
    for (auto p2 : e.getState().getPlayers()) {
        if (IAPos.x == (p2.second->getPokemon()->getPosition().x + 1) && IAPos.y ==  (p2.second->getPokemon()->getPosition().y) && !(p2.second->getIA())) {
            switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                case WEST:
                    e.addCommand(new AttackCommand(player), 1);
                    break;
                default:
                    e.addCommand(new MoveCommand(WEST, player), 1);
                    break;
            }
            return;
        }
        if (IAPos.x == (p2.second->getPokemon()->getPosition().x - 1) && IAPos.y ==  (p2.second->getPokemon()->getPosition().y) && !(p2.second->getIA())) {

            switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                case EST:
                    e.addCommand(new AttackCommand(player), 1);
                    break;
                default:
                    e.addCommand(new MoveCommand(EST, player), 1);
                    break;
            }
            return;
        }
        if (IAPos.y == (p2.second->getPokemon()->getPosition().y + 1) && IAPos.x ==  (p2.second->getPokemon()->getPosition().x) && !(p2.second->getIA())) {

            switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                case NORTH:
                    e.addCommand(new AttackCommand(player), 1);
                    break;
                default:
                    e.addCommand(new MoveCommand(NORTH, player), 1);
                    break;
            }
            return;
        }
        if (IAPos.y == (p2.second->getPokemon()->getPosition().y - 1) && IAPos.x ==  (p2.second->getPokemon()->getPosition().x) && !(p2.second->getIA())) {

            switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation() && !(p2.second->getIA())) {
                case SOUTH:
                    e.addCommand(new AttackCommand(player), 1);
                    break;
                default:
                    e.addCommand(new MoveCommand(SOUTH, player), 1);
                    break;
            }
            return;
        }


    }

    AstarComputer astarComputer(e.getState().getMap().get())
}

