#include <utility>

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

Engine::Engine(shared_ptr<mutex> m,State s):commands_mutex(std::move(m)),currentState(std::move(s))
{}
void engine::Engine::addCommand(shared_ptr<Command> command, unsigned int priority) {
    if(!command)
    {
        throw new runtime_error("empty command error");
    }

//    cout << "new adding command"<< endl;
commands_mutex->lock();
if(commands.find(priority) == commands.cend())
    commands[priority] = command;
else{
    priority = static_cast<unsigned int>(commands.size());
    commands[priority] = command;

}
commands_mutex->unlock();
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
            case ACTION_LV:
                break;
        }
    }
}

void engine::Engine::runCommands() {


//    cerr << "begin to run commands" <<endl;
    commands_mutex->lock();
    unique_ptr<map<int,shared_ptr<Command>>> commands_buffer;
    commands_buffer.reset(new map<int,shared_ptr<Command>>(commands));
    commands.clear();
    commands_mutex->unlock();
    auto it = commands_buffer->begin();
    while(it!=commands_buffer->cend())
    {

        if(this->getState().getPlayers()[it->first] && this->getState().getPlayers()[it->first]->getPokemon()
        && this->getState().getPlayers()[it->first]->getPokemon()->getAlive()){
        //if(this->getState().getPlayers()[it->first]->getPokemon()->getAlive()){
//        exec_cmd_mutex->lock();
            auto prevState = it->second->execute(currentState);
            previous_commands.push(prevState);
//        exec_cmd_mutex->unlock();
        }
        it++;
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

