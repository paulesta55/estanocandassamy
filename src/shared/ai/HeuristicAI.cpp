//
// Created by paul on 13/11/18.
//

#include "HeuristicAI.h"
#include "ai.h"
#include "engine.h"
#include "state.h"
#include <cmath>
#include "AStar.hpp"
#include <iostream>
#include <climits>
#include "MiniMax.h"


using namespace engine;
using namespace ai;
using namespace state;
using namespace std;
using namespace AStar;
using namespace MiniMax;


void ai::HeuristicAI::run(engine::Engine &e, unsigned int player, unsigned int enemy) {

    unsigned int enemyLife = e.getState().getPlayers()[enemy]->getPokemon()->getCurrentLife();
    unsigned int currentLife = e.getState().getPlayers()[player]->getPokemon()->getCurrentLife();

    Position IAPos = e.getState().getPlayers()[player]->getPokemon()->getPosition();
    Position enemyP = e.getState().getPlayers()[enemy]->getPokemon()->getPosition();
    if (currentLife != e.getState().getPlayers()[player]->getPokemon()->getFullLife()
        && currentLife < enemyLife) {
        if (AIUtils::computeD(IAPos, enemyP) < 2) {
            cerr << "Heuristic AI flees" << endl;
            AIUtils::flee(e, player, enemy);
        } else e.addCommand(make_shared<HealCommand>(player), player);
        return;
    }
    for (const auto &p2 : e.getState().getPlayers()) {
        if (p2.second) {


            if (IAPos.x == (p2.second->getPokemon()->getPosition().x + 1) &&
                IAPos.y == (p2.second->getPokemon()->getPosition().y) /*&& !(p2.second->getIA())*/) {
                switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                    case WEST:
                        e.addCommand(make_shared<AttackCommand>(player), player);
                        break;
                    default:
                        e.addCommand(make_shared<MoveCommand>(WEST, player), player);
                        break;
                }
                return;
            }
            if (IAPos.x == (p2.second->getPokemon()->getPosition().x - 1) &&
                IAPos.y == (p2.second->getPokemon()->getPosition().y) /*&& !(p2.second->getIA())*/) {

                switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                    case EST:
                        e.addCommand(make_shared<AttackCommand>(player), player);
                        break;
                    default:
                        e.addCommand(make_shared<MoveCommand>(EST, player), player);
                        break;
                }
                return;
            }
            if (IAPos.y == (p2.second->getPokemon()->getPosition().y + 1) &&
                IAPos.x == (p2.second->getPokemon()->getPosition().x) /*&& !(p2.second->getIA())*/) {

                switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                    case NORTH:
                        e.addCommand(make_shared<AttackCommand>(player), player);
                        break;
                    default:
                        e.addCommand(make_shared<MoveCommand>(NORTH, player), player);
                        break;
                }
                return;
            }
            if (IAPos.y == (p2.second->getPokemon()->getPosition().y - 1) &&
                IAPos.x == (p2.second->getPokemon()->getPosition().x) /*&& !(p2.second->getIA())*/) {

                switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation() && !(p2.second->getIA())) {
                    case SOUTH:
                        e.addCommand(make_shared<AttackCommand>(player), player);
                        break;
                    default:
                        e.addCommand(make_shared<MoveCommand>(SOUTH, player), player);
                        break;
                }
                return;
            }


        }
    }
    Position objectif = e.getState().getPlayers()[enemy]->getPokemon()->getPosition();
    Position current = e.getState().getPlayers()[player]->getPokemon()->getPosition();
    double distance = static_cast<int>(sqrt(
            pow(((int) (objectif.x) - (int) (current.x)), 2) + pow(((int) (objectif.y) - (int) (current.y)), 2)));
    cerr << "distance" << distance << endl;
    unsigned int area = restrictArea ? 5 : INT_MAX;
    if (distance < area) {
        AStar::Generator generator;
        int width = (int) (e.getState().getMap()->getWidth());
        int height = (int) (e.getState().getMap()->getHeight());
        generator.setWorldSize({(int) (e.getState().getMap()->getWidth()), (int) (e.getState().getMap()->getHeight())});
        generator.setHeuristic(AStar::Heuristic::manhattan);
        int k = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (e.getState().getMap()->getLayers()->at(0).getData()->at(k) != 35) {
                    Vec2i v;
                    v.x = j;
                    v.y = i;
                    generator.addCollision(v);
                }
                k++;
            }
        }
        Vec2i srce, obj;
        srce.x = current.x;
        srce.y = current.y;

        obj.x = objectif.x;
        obj.y = objectif.y;
        auto path = generator.findPath(srce, obj);


        auto nextTile = path[path.size() - 2];

        cerr << nextTile.x << " " << nextTile.y << endl;
        if (current.x == (unsigned int) nextTile.x) {
            if (current.y == (unsigned int) (nextTile.y - 1)) {
                e.addCommand(make_shared<MoveCommand>(SOUTH, player), player);

            } else {
                e.addCommand(make_shared<MoveCommand>(NORTH, player), player);
            }
        } else {
            if (current.x == (unsigned int) (nextTile.x - 1)) {
                e.addCommand(make_shared<MoveCommand>(EST, player), player);
            } else {
                e.addCommand(make_shared<MoveCommand>(WEST, player), player);
            }
        }
    }
}

