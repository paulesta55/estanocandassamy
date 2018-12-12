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

void engine::Engine::runCommands() {

    auto it = commands.begin();
//    cerr << "begin to run commands" <<endl;
    while(it!=commands.cend())
    {
        if(this->getState().getPlayers()[it->first]->getPokemon()->getAlive()) {
            it->second->execute(currentState);

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

