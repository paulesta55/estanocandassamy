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

void DeepAI::run (engine::Engine& e, unsigned int player, unsigned int enemy) {
    unique_ptr<MinMaxGenerator> generator(new MinMaxGenerator);
    shared_ptr<Engine> engine = make_shared<Engine>(e);
    State s = engine->getState();
    BestAction action = generator->compute(s,3,player,enemy);
    switch(action.getActionType()) {
        case 0: {
            cout << "ai : MOVE CL" << endl;
            unique_ptr<AI> ai;

            ai.reset(new HeuristicAI);
            ai->restrictArea = false;
            ai->run(e,player, enemy);
//            engine->runCommands();
            }
            break;

        case 1: {
            cout << "ai : MOVE AW" << endl;
            //check position according to enemyOrient
            AIUtils::flee(e,player,enemy);

            }
            break;
        case 2 : {
            cout << "ai : ATTACK" << endl;
            e.addCommand(make_shared<AttackCommand>(player), player);
//            engine->runCommands();
        }
            break;

        case 3: {
            cout << "ai : HEAL" << endl;

            // if player wounded playerPV+=1 else does nothing
            e.addCommand(make_shared<engine::HealCommand>(player), player);
//            engine->runCommands();
        }
        break;
    }
    cout << "cost "<<action.getCost()<< " action " << action.getActionType()<< endl ;
}