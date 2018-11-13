//
// Created by paul on 12/11/18.
//

#include <memory>
#include "RandomAI.h"
#include <iostream>
#include <engine.h>
#include <engine/AttackCommand.h>
#include <engine/MoveCommand.h>
#include <cstdlib>
#include <engine/HealCommand.h>

using namespace state;
using namespace std;
using namespace engine;

void ai::RandomAI::run(Engine &e, unsigned int player) {
    Position IAPos = e.getState().getPlayers()[player]->getPokemon()->getPosition();
    if (e.getState().getPlayers()[player]->getPokemon()->getCurrentLife() != e.getState().getPlayers()[player]
            ->getPokemon()->getFullLife()) {
        e.addCommand(new HealCommand(player), 1);
    }
    for (auto p2 : e.getState().getPlayers()) {
        if (IAPos.x == (p2.second->getPokemon()->getPosition().x + 1) && !(p2.second->getIA())) {
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
        if (IAPos.x == (p2.second->getPokemon()->getPosition().x - 1) && !(p2.second->getIA())) {
            switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                case EST:
                    e.addCommand(new AttackCommand(player), 1);
                default:
                    e.addCommand(new MoveCommand(EST, player), 1);
                    break;
            }
            return;
        }
        if (IAPos.y == (p2.second->getPokemon()->getPosition().y + 1) && !(p2.second->getIA())) {
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
        if (IAPos.y == (p2.second->getPokemon()->getPosition().y - 1)) {
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

    int choice = rand() % 4;
    Orientation o;
    switch (choice) {
        case 0:
            o = SOUTH;
            break;
        case 1:
            o = NORTH;
            break;
        case 2:
            o = EST;
            break;
        case 3:
            o = WEST;
            break;
    }
    e.addCommand(new MoveCommand(o, player), 1);

}

