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
#include <engine/Engine.h>
#include "ai.h"
#include "AIUtils.h"
using namespace MiniMax;

using namespace engine;
using namespace ai;

BestAction MinMaxGenerator::tour(State s, MinMax m, uint epoch, uint playerId, uint enemyId,ActionType previousAction) {
    if(epoch<=0) {
        return {this->computeCost(s,enemyId,playerId),previousAction};
    }
    else {
        int cost = m == MAX?INT_MIN:INT_MAX;
        ActionType action;
        for(int i =0; i<4;i++) {
            auto tempAction = static_cast<ActionType >(i);
//            cout << "temp action " << tempAction <<endl;
            // clone the state so that the current state is not impacted by the AI
            // TODO: create and use a "lightweight state" only used by the AI
            State newState = s;
            newState.unregisterObservers();
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
            Engine e(newState);

            Position objectif = e.getState().getPlayers()[enemyId]->getPokemon()->getPosition();
            Position current = e.getState().getPlayers()[playerId]->getPokemon()->getPosition();
            Orientation enemyOrient = e.getState().getPlayers()[enemyId]->getPokemon()->getOrientation();

            auto actionType = static_cast<ActionType>(i);
            switch(actionType) {
                case MOVE_CL: {
                    unique_ptr<AI> ai;
                    ai.reset(new HeuristicAI);
                    ai->run(e,playerId,enemyId);
                    e.runCommands();
                }
                    break;
                case MOVE_AW:
                    // go to enemy orientation if possible. If not go to the first possible location
                {
                    moveAw(e, current,enemyOrient,playerId,objectif);
                    e.runCommands();
                }
                    break;
                case ActionType::ATTACK: {
                    // if player can attack then enemyPV-=1 else does nothing
                    e.addCommand(make_shared<AttackCommand>(playerId),playerId);
                    e.runCommands();
                }
                    break;
                case ActionType::HEAL : {
                    // if player wounded playerPV+=1 else does nothing
                    e.addCommand(make_shared<HealCommand>(playerId), playerId);
                    e.runCommands();
                }
                    break;
            }
            if(m == MinMax::MAX) {
                auto bestAction= tour(newState,MIN,epoch-1,enemyId,playerId,tempAction);
//                int tempCost = tour(enginePtr->getState(),MIN,epoch-1,enemyId,playerId,tempAction).getCost();
                if(bestAction.getCost()> cost) {
                    cost = bestAction.getCost();
                    action = bestAction.getActionType();
                }
//                cout << "cost " << cost << endl;
//                cout << "action " << action << endl;
            }
            else {
                auto bestAction= tour(newState,MAX,epoch-1,enemyId,playerId,tempAction);
                if(bestAction.getCost()< cost) {
                    cost = bestAction.getCost();
                    action = bestAction.getActionType();
                }
//                cout << "cost " << cost << endl;
//                cout << "action " << action << endl;

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
    int cost = 0;
//    if(s.getPlayers()[playerId]->getPokemon()->getCurrentLife() >=  s.getPlayers()[playerId]->getPokemon()->getCurrentLife())
    cost = s.getPlayers()[playerId]->getPokemon()->getCurrentLife()-s.getPlayers()[enemyId]->getPokemon()->getCurrentLife()-distance;
//    else cost = s.getPlayers()[playerId]->getPokemon()->getCurrentLife()-s.getPlayers()[enemyId]->getPokemon()->getCurrentLife()+distance;

    return cost;
}

bool MinMaxGenerator::checkCase(Position p, State& s) {
    uint tileNumber = p.x + p.y * s.getMap()->getWidth();
    return s.getMap()->getLayers()->at(0).getData()->at(tileNumber) == 35;
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
    cout << "cost end compute :" << action.getCost() <<endl;
    return action;
}

void MinMaxGenerator::moveAw(Engine& enginePtr, Position current, Orientation enemyOrient, uint playerId,
        Position objectif) {
    AIUtils::flee(enginePtr,playerId);

}
