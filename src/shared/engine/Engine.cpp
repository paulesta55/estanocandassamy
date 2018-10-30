//
// Created by paul on 28/10/18.
//
#include "engine.h"
#include "Engine.h"
#include "string.h"
#include "state.h"
using namespace std;
using namespace engine;
using namespace state;

Engine::Engine()
{
    static unsigned int id = 0;

    string player = "Alice";
    currentState.getPlayers().insert(make_pair(id,new Player(false,player,id,make_shared<Bulbizarre>(id))));

}
void engine::Engine::addCommand(Command* command, unsigned int priority) {
    shared_ptr<Command> command_shared;
    command_shared.reset(command);
    commands.insert(make_pair(priority,command_shared));
}

void engine::Engine::runCommands() {

    auto it = commands.begin();
    while(it!=commands.cend())
    {
        it->second->execute(currentState);
        it++;
    }
}

state::State &engine::Engine::getState() {
    return currentState;
}

std::stack<std::shared_ptr<engine::Command>> engine::Engine::update() {
    return std::stack<std::shared_ptr<engine::Command>>();
}


