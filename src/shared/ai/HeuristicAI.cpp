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
using namespace engine;
using namespace ai;
using namespace state;
using namespace std;
using namespace AStar;

void ai::HeuristicAI::run(engine::Engine &e, unsigned int player) {

    Position IAPos = e.getState().getPlayers()[player]->getPokemon()->getPosition();
    if (e.getState().getPlayers()[player]->getPokemon()->getCurrentLife() != e.getState().getPlayers()[player]
            ->getPokemon()->getFullLife() && e.getState().getPlayers()[player]->getPokemon()->getCurrentLife() <
                                                             e.getState().getPlayers()[0]->getPokemon()->getCurrentLife()) {
        e.addCommand(make_shared<HealCommand>(player), 1);

        return;
    }
    for (auto p2 : e.getState().getPlayers()) {
        if (IAPos.x == (p2.second->getPokemon()->getPosition().x + 1) && IAPos.y ==  (p2.second->getPokemon()->getPosition().y) && !(p2.second->getIA())) {
            switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                case WEST:
                    e.addCommand(make_shared<AttackCommand>(player), 1);
                    break;
                default:
                    e.addCommand(make_shared<MoveCommand>(WEST, player), 1);
                    break;
            }
            return;
        }
        if (IAPos.x == (p2.second->getPokemon()->getPosition().x - 1) && IAPos.y ==  (p2.second->getPokemon()->getPosition().y) && !(p2.second->getIA())) {

            switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                case EST:
                    e.addCommand(make_shared<AttackCommand>(player), 1);
                    break;
                default:
                    e.addCommand(make_shared<MoveCommand>(EST, player), 1);
                    break;
            }
            return;
        }
        if (IAPos.y == (p2.second->getPokemon()->getPosition().y + 1) && IAPos.x ==  (p2.second->getPokemon()->getPosition().x) && !(p2.second->getIA())) {

            switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation()) {
                case NORTH:
                    e.addCommand(make_shared<AttackCommand>(player), 1);
                    break;
                default:
                    e.addCommand(make_shared<MoveCommand>(NORTH, player), 1);
                    break;
            }
            return;
        }
        if (IAPos.y == (p2.second->getPokemon()->getPosition().y - 1) && IAPos.x ==  (p2.second->getPokemon()->getPosition().x) && !(p2.second->getIA())) {

            switch (e.getState().getPlayers()[player]->getPokemon()->getOrientation() && !(p2.second->getIA())) {
                case SOUTH:
                    e.addCommand(make_shared<AttackCommand>(player), 1);
                    break;
                default:
                    e.addCommand(make_shared<MoveCommand>(SOUTH, player), 1);
                    break;
            }
            return;
        }


    }
    Position objectif = e.getState().getPlayers()[0]->getPokemon()->getPosition();
    Position current = e.getState().getPlayers()[player]->getPokemon()->getPosition();
//    auto h = static_cast<unsigned int>(std::sqrt(((int)(objectif.x) - (int)(current.x)) * ((int) (objectif.x) - (int)
//            (current.x)) + ((int)(objectif.y) - (int)(current.y)) * ((int)(objectif.y)-(int)(current.y))));
//
//    shared_ptr<Node> n=make_shared<Node>(nullptr,Position(),0,0);
//    Node objectifNode(n,e.getState().getPlayers()[0]->getPokemon()->getPosition(),0,0);
//    Node source(n,current,0,h);
//    AstarComputer astarComputer(e.getState().getMap(),objectifNode,source);
//    auto c = astarComputer.compute();
//TODO : use AstarComputer
//TODO : add a static int computeHeuristic method to AstarComputer
//Node objectif(nullptr,e.getState().getPlayers()[0]->getPokemon()->getPosition(),0,)//TODO: change the hardcoded ID
//AstarComputer astarComputer(e.getState().getMap(),);

    AStar::Generator generator;
    int width = (int)(e.getState().getMap()->getWidth());
    int height = (int)(e.getState().getMap()->getHeight());
    generator.setWorldSize({(int)(e.getState().getMap()->getWidth()), (int)(e.getState().getMap()->getHeight())});
    generator.setHeuristic(AStar::Heuristic::manhattan);
//    generator.setDiagonalMovement(false);
    int k = 0;
    for (int i =0 ; i<height; i++ )
    {
        for (int j = 0 ; j<width; j++)
        {
            if(e.getState().getMap()->getLayers()->at(0).getData()->at(k)!=35)
            {
                Vec2i v;
                v.x = j;
                v.y = i;
                generator.addCollision(v);
            }
            k++;
        }
    }
    Vec2i srce,obj;
    srce.x = current.x;
    srce.y = current.y;

    obj.x = objectif.x;
    obj.y = objectif.y;
    auto path = generator.findPath(srce,obj);
    for(auto c : path)
    {
        cout << c.x << " " << c.y <<endl;
    }

    auto nextTile = path[path.size()-2];

    cout << nextTile.x << " " << nextTile.y <<endl;
    if(current.x ==(unsigned int) nextTile.x)
    {
        if(current.y == (unsigned int)(nextTile.y-1)) {
            e.addCommand(make_shared<MoveCommand>(SOUTH,player),1);

        }
        else {
            e.addCommand(make_shared<MoveCommand>(NORTH,player),1);
        }
    }
    else {
        if(current.x == (unsigned int)(nextTile.x-1)) {
            e.addCommand(make_shared<MoveCommand>(EST,player),1);
        }
        else {
            e.addCommand(make_shared<MoveCommand>(WEST,player),1);        }
    }

}

