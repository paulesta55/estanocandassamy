//
// Created by paul on 30/11/18.
//

#include "MiniMax.h"
#include "DeepAI.h"
#include <iostream>
#include "ai.h"
#include "engine.h"

using namespace std;
using namespace state;
using namespace MiniMax;
using namespace engine;
using namespace ai;

void DeepAI::run (engine::Engine& e, unsigned int player) {
    unique_ptr<MinMaxGenerator> generator;
    State s = e.getState();
    BestAction action = generator->compute(s,3,player,0);

    cout << "cost "<<action.getCost()<< " action " << action.getActionType()<< endl ;
}