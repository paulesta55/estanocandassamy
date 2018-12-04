//
// Created by paul on 20/11/18.
//

#ifndef MINIMAX_MINIMAX_H
#define MINIMAX_MINIMAX_H

#include "state.h"
#include "engine.h"
using namespace state;
using namespace std;
using namespace engine;
unsigned int typedef uint;
namespace MiniMax {

    enum ActionType{
        MOVE_CL = 0,
        MOVE_AW = 1,
        ATTACK = 2,
        HEAL = 3,
    };

    enum MinMax{
        MIN,
        MAX
    };


    class BestAction{
    private:
        ActionType action;
        int cost;
    public:
        BestAction(int cost,ActionType action):action(action), cost(cost){};
        ActionType getActionType() {return action;};
        int getCost() {return cost;};
    };

    class MinMaxGenerator {
    private:
        shared_ptr<State> state;
        BestAction tour(State,MinMax,uint epoch,uint playerId, uint enemyId,ActionType);
        int computeCost(State&, uint enemyId, uint playerId);


    public:
        static void moveAw(shared_ptr<Engine> e,Position current, Orientation enemyOrient, uint playerId,Position objectif);
        BestAction compute(State s,uint epoch,uint playerId, uint enemyId);
        static bool checkCase(Position, State&);
        static vector<Orientation> findNeighbors(Position&,State&,Position&);
    };



};



#endif //MINIMAX_MINIMAX_H
