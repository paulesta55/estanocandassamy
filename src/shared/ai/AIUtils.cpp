//
// Created by paul on 12/5/18.
//
#include "AIUtils.h"
#include "ai.h"
#include "state.h"
#include "engine.h"
#include "MiniMax.h"
#include "iostream"

using namespace engine;
using namespace state;
using namespace std;
using namespace ai;

void AIUtils::flee(Engine& e, unsigned int player) {

    Position IAPos = e.getState().getPlayers()[player]->getPokemon()->getPosition();
    Position enemyP = e.getState().getPlayers()[0]->getPokemon()->getPosition();
    auto currentO = e.getState().getPlayers()[player]->getPokemon()->getOrientation();
    auto nextAIP = nextP(IAPos,currentO);
    if(nextAIP.y != enemyP.y && nextAIP.x != enemyP.x) e.addCommand(make_shared<MoveCommand>(currentO,player),player);
    else {
        if(enemyP.x == IAPos.x - 1 ) {
            if(MiniMax::MinMaxGenerator::checkCase(Position(IAPos.x+1,IAPos.y),e.getState())) e.addCommand(make_shared<MoveCommand>(EST,player),player);
            else {
                auto possibleP = MiniMax::MinMaxGenerator::findNeighbors(IAPos,e.getState(),enemyP);
                if(!possibleP.empty()) e.addCommand(make_shared<MoveCommand>(possibleP[0],player),player);
            }
        }
        else if(enemyP.x == IAPos.x + 1) {
            if(MiniMax::MinMaxGenerator::checkCase(Position(IAPos.x-1,IAPos.y),e.getState())) e.addCommand(make_shared<MoveCommand>(WEST,player),player);
            else {
                auto possibleP = MiniMax::MinMaxGenerator::findNeighbors(IAPos,e.getState(),enemyP);
                if(!possibleP.empty()) e.addCommand(make_shared<MoveCommand>(possibleP[0],player),player);
            }
        }
        else if(enemyP.y == IAPos.y - 1) {
            if(MiniMax::MinMaxGenerator::checkCase(Position(IAPos.x,IAPos.y+1),e.getState())) e.addCommand(make_shared<MoveCommand>(SOUTH,player),player);
            else {
                auto possibleP = MiniMax::MinMaxGenerator::findNeighbors(IAPos,e.getState(),enemyP);
                if(!possibleP.empty()) e.addCommand(make_shared<MoveCommand>(possibleP[0],player),player);
            }
        }
        else if(enemyP.y == IAPos.y + 1) {
            if(MiniMax::MinMaxGenerator::checkCase(Position(IAPos.x,IAPos.y-1),e.getState())) e.addCommand(make_shared<MoveCommand>(NORTH,player),player);
            else {
                auto possibleP = MiniMax::MinMaxGenerator::findNeighbors(IAPos,e.getState(),enemyP);
                if(!possibleP.empty()) e.addCommand(make_shared<MoveCommand>(possibleP[0],player),player);
            }
        }
    }
}

unsigned int AIUtils::computeD(state::Position p1, state::Position p2) {
    return static_cast<unsigned int>(abs(static_cast<int >(p1.y) - static_cast<int>(p2.y)) + abs(static_cast<int >(p1.x)
                                                                                                 - static_cast<int>(p2.x)));
}

state::Position AIUtils::nextP(state::Position p, state::Orientation o) {
    switch(o) {
        case SOUTH: {
            return Position(p.x,p.y+1);
        }
        case NORTH: {
            return Position(p.x,p.y-1);
        }
        case WEST: {
            return Position(p.x-1,p.y);
        }
        case EST: {
            return Position(p.x+1,p.y);
        }
        default:
            cerr << "bad orientation in Heuristic AI::run" << endl;
            break;
    }
    return {};
}
