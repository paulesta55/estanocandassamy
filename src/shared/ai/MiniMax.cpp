//
// Created by paul on 20/11/18.
//

#include "MiniMax.h"
#include "AStar.hpp"
#include "engine.h"
#include <climits>
#include <cmath>
#include "AStar.hpp"
#include <iostream>
using namespace MiniMax;

using namespace engine;
using namespace AStar;

BestAction MinMaxGenerator::tour(State s, MinMax m, uint epoch, uint playerId, uint enemyId,ActionType previousAction) {
    if(epoch<=0) {
        return BestAction(this->computeCost(s,enemyId,playerId),previousAction);
    }
    else {
        int cost = m == MAX?0:INT_MAX;
        ActionType action;
        for(int i =0; i<4;i++) {
            ActionType tempAction;
            State newState = s;
            Engine engine(s);
            Position objectif = engine.getState().getPlayers()[enemyId]->getPokemon()->getPosition();
            Position current = engine.getState().getPlayers()[playerId]->getPokemon()->getPosition();
            Orientation enemyOrient = engine.getState().getPlayers()[enemyId]->getPokemon()->getOrientation();

            ActionType actionType = static_cast<ActionType>(i);
            switch(actionType) {
                case MOVE_CL: {
                    // use AStar AI
                    AStar::Generator generator;
                    int width = (int) (engine.getState().getMap()->getWidth());
                    int height = (int) (engine.getState().getMap()->getHeight());
                    generator.setWorldSize({(int) (engine.getState().getMap()->getWidth()),
                                            (int) (engine.getState().getMap()->getHeight())});
                    generator.setHeuristic(AStar::Heuristic::manhattan);
                    int k = 0;
                    for (int _i = 0; _i < height; _i++) {
                        for (int j = 0; j < width; j++) {
                            if (engine.getState().getMap()->getLayers()->at(0).getData()->at(k) != 35) {
                                Vec2i v;
                                v.x = j;
                                v.y = _i;
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
//                    cout << nextTile.x << " " << nextTile.y << endl;
                    Position p(nextTile.x, nextTile.y);
                    engine.getState().getPlayers()[playerId]->getPokemon()->setPosition(p);
                    tempAction = MOVE_CL;
                }
                    break;
                case MOVE_AW:
                    // go to enemy orientation if possible. If not go to the first possible location
                {
                    bool oppositeOrient = false;
                    //check position according to enemyOrient
                    switch (enemyOrient) {
                        case SOUTH:
                            oppositeOrient = checkCase(Position(current.x, current.y + 1), engine.getState());
                            break;
                        case EST:
                            oppositeOrient = checkCase(Position(current.x + 1, current.y), engine.getState());
                            break;
                        case NORTH:
                            oppositeOrient = checkCase(Position(current.x, current.y - 1), engine.getState());
                            break;
                        case WEST:
                            oppositeOrient = checkCase(Position(current.x - 1, current.y), engine.getState());
                            break;
                    }
                    if (oppositeOrient) {
                        engine.addCommand(make_shared<MoveCommand>(enemyOrient, playerId), 0);
                    } else {
                        auto neighbors = findNeighbors(current, engine.getState(), objectif);
                        engine.addCommand(make_shared<MoveCommand>(neighbors[0], playerId), 0);
                    }
                    engine.runCommands();
                    tempAction = MOVE_AW;
                }
                    break;
                case ActionType::ATTACK: {
                    // if player can attack then enemyPV-=1 else does nothing

                    engine.addCommand(make_shared<AttackCommand>(playerId),0);
                    engine.runCommands();
                    tempAction = ATTACK;
                }
                    break;
                case ActionType::HEAL : {
                    tempAction = HEAL;
                    // if player wounded playerPV+=1 else does nothing
                    engine.addCommand(make_shared<HealCommand>(playerId), 0);
                    engine.runCommands();
                }
                    break;
            }
            epoch--;
            if(m == MinMax::MAX) {
                int tempCost = tour(engine.getState(),MIN,epoch,enemyId,playerId,tempAction).getCost();
                cost = tempCost > cost?tempCost:cost;
                action = tempCost > cost?tempAction:action;
                cout << "cost " << cost << endl;
            }
            else {
                int tempCost = tour(newState,MAX,epoch,enemyId,playerId,tempAction).getCost();
                cost = tempCost < cost?tempCost:cost;
                cout << "cost " << cost << endl;
                action = tempCost < cost?tempAction:action;
            }
        }
        return BestAction(cost,action);
    }
}

int MinMaxGenerator::computeCost(State& s, uint enemyId, uint playerId) {
    Position enemyP=s.getPlayers()[enemyId]->getPokemon()->getPosition();
    Position currentP = s.getPlayers()[playerId]->getPokemon()->getPosition();
    // use manhattan formula * 10
    uint  distance = static_cast<uint >(10*(abs((int)(enemyP.x)-(int)currentP.x))+abs((int)enemyP.y-(int)(currentP.y)));
    int cost = s.getPlayers()[playerId]->getPokemon()->getCurrentLife()-s.getPlayers()[enemyId]->getPokemon()->getCurrentLife()-distance;
    return 0;
}

bool MinMaxGenerator::checkCase(Position p, State& s) {
    uint tileNumber = p.x + p.y * s.getMap()->getWidth();
    if(s.getMap()->getLayers()->at(0).getData()->at(tileNumber)!=35) {
        return true;
    }
    return false;
}

vector<Orientation> MinMaxGenerator::findNeighbors(Position& p, State& s,Position& forbiddP) {
    vector<Orientation> neighbors;
    for(int k = 0; k<4;k++) {
        auto o = static_cast<Orientation >(k);
        switch(o) {
            case SOUTH:{
                Position southP = Position(p.x,p.y+1);
                if(checkCase(southP,s) && southP.x != forbiddP.x && southP.y != forbiddP.y) {
                    neighbors.push_back(SOUTH);
                }}
                break;
            case NORTH:{
                Position northP = Position(p.x, p.y-1);
                if(checkCase(northP,s) && northP.x != forbiddP.x && northP.y != forbiddP.y) {
                    neighbors.push_back(NORTH);
                }}
                break;
            case EST:{
                Position estP= Position(p.x+1, p.y);
                if(checkCase(estP,s) && estP.x != forbiddP.x && estP.y != forbiddP.y) {
                    neighbors.push_back(EST);
                }}
                break;
            case WEST: {
                Position westP= Position(p.x-1, p.y);
                if(checkCase(westP,s) && westP.x != forbiddP.x && westP.y != forbiddP.y) {
                    neighbors.push_back(WEST);
                }}
                break;
        }
    }
    return neighbors;

}

BestAction MinMaxGenerator::compute(State s,uint epoch,uint playerId, uint enemyId) {
    BestAction action =this->tour(s, MAX, epoch, playerId, enemyId,HEAL);
    return action;
}
