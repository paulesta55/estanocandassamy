#include <utility>

//
// Created by paul on 28/10/18.
//
#include "engine.h"
#include "Engine.h"
#include "string.h"
#include "state.h"
#include <iostream>
using namespace std;
using namespace engine;
using namespace state;

Engine::Engine(State s):currentState(std::move(s))
{

    unsigned int id = 1;

    string player = "Alice";
    this->currentState.getPlayers().insert(make_pair(id,new Player(false,player,id,make_shared<Bulbizarre>(id,WEST
            ,200,Position(3,9)))));
    unsigned int id2 = 0;
    string player2 = "Bob";
    this->currentState.getPlayers().insert(make_pair(id2,new Player(true,player2,id2,make_shared<Salameche>(id2,EST
            ,150,Position(20,20)))));
    this->currentState.center = Position(7,7);


}
void engine::Engine::addCommand(Command* command, unsigned int priority) {
    if(!command)
    {
        throw new runtime_error("empty command error");
    }
    shared_ptr<Command> command_shared;
    command_shared.reset(command);
//    cout << "new adding command"<< endl;
    commands.insert(make_pair(priority,command_shared));

//    cout << "new command added" <<endl;
}

void engine::Engine::runCommands() {

    auto it = commands.begin();
//    cout << "begin to run commands" <<endl;
    while(it!=commands.cend())
    {
//        cout <<"command "<<it->first<<endl;
        it->second->execute(currentState);
        bool endbool = it == commands.cend();
//        cout << "end of commands ? " << endbool << endl;

        commands.erase(it);
        //        commands.erase(it);
        it++;
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

