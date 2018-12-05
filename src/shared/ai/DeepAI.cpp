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
    shared_ptr<Engine> engine = make_shared<Engine>(e);
    State s = engine->getState();
    BestAction action = generator->compute(s,5,player,0);
    switch(action.getActionType()) {
        case 0: {
            cout << "ai : MOVE CL" << endl;
            unique_ptr<AI> ai;
            ai.reset(new HeuristicAI);
            ai->run(e,player);
//            engine->runCommands();
            }
            break;

        case 1: {
            cout << "ai : MOVE AW" << endl;
            bool oppositeOrient = false;
            //check position according to enemyOrient
            switch (s.getPlayers()[0]->getPokemon()->getOrientation()) {
                case SOUTH:
                    oppositeOrient = MinMaxGenerator::checkCase(Position(s.getPlayers()[player]->getPokemon()->getPosition().x, s.getPlayers()[player]->getPokemon()->getPosition().y + 1), s);
                    break;
                case EST:
                    oppositeOrient = MinMaxGenerator::checkCase(Position(s.getPlayers()[player]->getPokemon()->getPosition().x + 1, s.getPlayers()[player]->getPokemon()->getPosition().y), s);
                    break;
                case NORTH:
                    oppositeOrient = MinMaxGenerator::checkCase(Position(s.getPlayers()[player]->getPokemon()->getPosition().x, s.getPlayers()[player]->getPokemon()->getPosition().y - 1), s);
                    break;
                case WEST:
                    oppositeOrient = MinMaxGenerator::checkCase(Position(s.getPlayers()[player]->getPokemon()->getPosition().x - 1, s.getPlayers()[player]->getPokemon()->getPosition().y), s);
                    break;
            }
            if (oppositeOrient) {
                e.addCommand(make_shared<MoveCommand>(s.getPlayers()[0]->getPokemon()->getOrientation(), player), 1);
            } else {
                auto playerP =s.getPlayers()[player]->getPokemon()->getPosition();
                auto enemyP =s.getPlayers()[0]->getPokemon()->getPosition();

                auto neighbors = MiniMax::MinMaxGenerator::findNeighbors(playerP,
                        s, enemyP);
                if(neighbors.size()>0) e.addCommand(make_shared<MoveCommand>(neighbors[0], player), 1);
                else e.addCommand(make_shared<HealCommand>(player),1);

            }
//            MiniMax::MinMaxGenerator::moveAw(engine,s.getPlayers()[player]->getPokemon()->getPosition(),
//                    s.getPlayers()[0]->getPokemon()->getOrientation(),player,s.getPlayers()[0]->getPokemon()->getPosition());
//            engine->runCommands();
            }
            break;
        case 2 : {
            cout << "ai : ATTACK" << endl;

            e.addCommand(make_shared<AttackCommand>(player), 1);
//            engine->runCommands();
        }
            break;

        case 3: {
            cout << "ai : HEAL" << endl;

            // if player wounded playerPV+=1 else does nothing
            e.addCommand(make_shared<HealCommand>(player), 1);
//            engine->runCommands();
        }
        break;
    }
    cout << "cost "<<action.getCost()<< " action " << action.getActionType()<< endl ;
}