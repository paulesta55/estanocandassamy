//
// Created by paul on 28/10/18.
//
#include "engine.h"
#include "Engine.h"
using namespace std;
using namespace engine;

void engine::Engine::addCommand(Command* command, unsigned int priority) {
    shared_ptr<Command> command_shared;
    command_shared.reset(command);
    commands.insert(make_pair(priority,command_shared));
}

void engine::Engine::runCommands() {


}

state::State &engine::Engine::getState() {
    return currentState;
}

std::stack<std::shared_ptr<engine::Command>> engine::Engine::update() {
    return std::stack<std::shared_ptr<engine::Command>>();
}


