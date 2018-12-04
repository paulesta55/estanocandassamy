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
        int cost = m == MAX?INT_MIN:INT_MAX;
        ActionType action;
        for(int i =0; i<4;i++) {
            ActionType tempAction;
            // clone the state so that the current state is not impacted by the AI
            // TODO: create and use a "lightweight state" only used by the AI
            State newState = s;
            auto it = newState.getPlayers().begin();
            while(it!=newState.getPlayers().cend()) {
                it->second = make_shared<Player>(*(it->second->clone()));
                shared_ptr<Pokemon> poke;
                switch(it->second->getPokemon()->getType()) {
                    case PokeType::BULBIZARRE :
                        poke.reset((Bulbizarre*)(it->second->getPokemon()->clone()));
                        break;
                    case SALAMECHE:
                        poke.reset((Salameche*)(it->second->getPokemon()->clone()));
                        break;
                    case CARAPUCE:
                        poke.reset((Carapuce*)(it->second->getPokemon()->clone()));
                        break;
                    default:
                        break;
                }

                it->second->setPokemon(poke);
                it++;
            }
            shared_ptr<Engine> enginePtr(new Engine(newState));

            Position objectif = enginePtr->getState().getPlayers()[enemyId]->getPokemon()->getPosition();
            Position current = enginePtr->getState().getPlayers()[playerId]->getPokemon()->getPosition();
            Orientation enemyOrient = enginePtr->getState().getPlayers()[enemyId]->getPokemon()->getOrientation();

            ActionType actionType = static_cast<ActionType>(i);
            switch(actionType) {
                case MOVE_CL: {
                    // use AStar AI
                    AStar::Generator generator;
                    int width = (int) (enginePtr->getState().getMap()->getWidth());
                    int height = (int) (enginePtr->getState().getMap()->getHeight());
                    generator.setWorldSize({(int) (enginePtr->getState().getMap()->getWidth()),
                                            (int) (enginePtr->getState().getMap()->getHeight())});
                    generator.setHeuristic(AStar::Heuristic::manhattan);
                    int k = 0;
                    for (int _i = 0; _i < height; _i++) {
                        for (int j = 0; j < width; j++) {
                            if (enginePtr->getState().getMap()->getLayers()->at(0).getData()->at(k) != 35) {
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
                    enginePtr->getState().getPlayers()[playerId]->getPokemon()->setPosition(p);
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
                            oppositeOrient = checkCase(Position(current.x, current.y + 1), enginePtr->getState());
                            break;
                        case EST:
                            oppositeOrient = checkCase(Position(current.x + 1, current.y), enginePtr->getState());
                            break;
                        case NORTH:
                            oppositeOrient = checkCase(Position(current.x, current.y - 1), enginePtr->getState());
                            break;
                        case WEST:
                            oppositeOrient = checkCase(Position(current.x - 1, current.y), enginePtr->getState());
                            break;
                    }
                    if (oppositeOrient) {
                        enginePtr->addCommand(make_shared<MoveCommand>(enemyOrient, playerId), 0);
                    } else {
                        auto neighbors = findNeighbors(current, enginePtr->getState(), objectif);
                        if(neighbors.size()>0) enginePtr->addCommand(make_shared<MoveCommand>(neighbors[0], playerId), 0);

                    }
                    enginePtr->runCommands();
                    tempAction = MOVE_AW;
                }
                    break;
                case ActionType::ATTACK: {
                    // if player can attack then enemyPV-=1 else does nothing

                    enginePtr->addCommand(make_shared<AttackCommand>(playerId),0);
                    enginePtr->runCommands();
                    tempAction = ATTACK;
                }
                    break;
                case ActionType::HEAL : {
                    tempAction = HEAL;
                    // if player wounded playerPV+=1 else does nothing
                    enginePtr->addCommand(make_shared<HealCommand>(playerId), 0);
                    enginePtr->runCommands();
                }
                    break;
            }
            if(m == MinMax::MAX) {
                int tempCost = tour(enginePtr->getState(),MIN,epoch-1,enemyId,playerId,tempAction).getCost();
                cost = tempCost > cost?tempCost:cost;
                action = tempCost > cost?tempAction:action;
                cout << "cost " << cost << endl;
            }
            else {
                int tempCost = tour(newState,MAX,epoch-1,enemyId,playerId,tempAction).getCost();
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
    uint  distance = static_cast<uint >((abs((int)(enemyP.x)-(int)currentP.x))+abs((int)enemyP.y-(int)(currentP.y)));
    int cost = s.getPlayers()[playerId]->getPokemon()->getCurrentLife()-s.getPlayers()[enemyId]->getPokemon()->getCurrentLife()-distance;
    return cost;
}

bool MinMaxGenerator::checkCase(Position p, State& s) {
    uint tileNumber = p.x + p.y * s.getMap()->getWidth();
    return s.getMap()->getLayers()->at(0).getData()->at(tileNumber) != 35;
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
