#include <utility>

//
// Created by paul on 28/10/18.
//
#include "engine.h"
#include "Engine.h"
#include "string.h"
#include "state.h"
#include <iostream>
#include <map>

using namespace std;
using namespace engine;
using namespace state;

Engine::Engine(State s):currentState(std::move(s))
{




}
void engine::Engine::addCommand(shared_ptr<Command> command, unsigned int priority) {
    if(!command)
    {
        throw new runtime_error("empty command error");
    }

//    cout << "new adding command"<< endl;
if(commands.find(priority) == commands.cend())
    commands[priority] = command;
else{
    priority = static_cast<unsigned int>(commands.size());
    commands[priority] = command;

}
//    cerr << "new command added" <<endl;
}

void engine::Engine::undoCommands(){
    if(!previous_commands.empty()){
        auto prevState = this->previous_commands.top();
        auto action = prevState->aType;
        this->previous_commands.pop();
        switch(action){
            case engine ::ACTION_ATT:{
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setAlive(true);
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setOrientation(prevState->previousO);
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setPosition(prevState->previousP);
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setCurrentLife(prevState->previousLife);
                StateEvent e(StateEventId::ALL_CHANGED);
                this->getState().notifyObservers(e);
                break;
            }
            case engine ::ACTION_HEAL:{
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setAlive(true);
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setOrientation(prevState->previousO);
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setPosition(prevState->previousP);
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setCurrentLife(prevState->previousLife);
                StateEvent e(StateEventId::ALL_CHANGED);
                this->getState().notifyObservers(e);
                break;
            }
            case engine ::ACTION_MV:{
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setAlive(true);
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setOrientation(prevState->previousO);
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setPosition(prevState->previousP);
                this->getState().getPlayers()[prevState->playerId]->getPokemon()->setCurrentLife(prevState->previousLife);
                StateEvent e(StateEventId::ALL_CHANGED);
                this->getState().notifyObservers(e);
                break;
            }
        }
    }
}

void engine::Engine::runCommands() {

    auto it = commands.begin();
//    cerr << "begin to run commands" <<endl;
    while(it!=commands.cend())
    {

        if(this->getState().getPlayers()[it->first]->getPokemon()->getAlive()){ 
            auto prevState = it->second->execute(currentState);
            previous_commands.push(prevState);
        }
        it = commands.erase(it);
        //        commands.erase(it);
    }


//    commands.clear();
//    cout << "end of commands" <<endl;
}

state::State &engine::Engine::getState() {
    return currentState;
}

std::stack<std::shared_ptr<engine::Command>> engine::Engine::update() {
    return std::stack<std::shared_ptr<engine::Command>>();
}

const std::map<int, std::shared_ptr<Command>> &Engine::getCommands() {
    return commands;
}

