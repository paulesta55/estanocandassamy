//
// Created by paul on 20/11/18.
//

#ifndef MINIMAX_MINIMAX_H
#define MINIMAX_MINIMAX_H

#include "state.h"
using namespace state;
using namespace std;
unsigned int typedef uint;
namespace MiniMax {

    enum ActionType{
        MOVE_CL=0,
        MOVE_AW=1,
        ATTACK=2,
        HEAL=3,
    };

    enum MinMax{
        MIN,
        MAX
    };

    class Action {
    public:
        virtual ActionType getActionType() = 0;
        virtual Action* clone() = 0;
    };

    class BestAction{
    private:
        ActionType action;
        int cost;
    public:
        BestAction(int cost,ActionType action):cost(cost),action(action) {};
        ActionType getActionType() {return action;};
        int getCost() {return cost;};
    };

    class MinMaxGenerator {
    private:
        shared_ptr<State> state;
        BestAction tour(State,MinMax,uint epoch,uint playerId, uint enemyId,ActionType);
        int computeCost(State&, uint enemyId, uint playerId);
        bool checkCase(Position, State&);
        vector<Orientation> findNeighbors(Position&,State&,Position&);
    public:
        BestAction compute(State s,uint epoch,uint playerId, uint enemyId);
    };



};



#endif //MINIMAX_MINIMAX_H
