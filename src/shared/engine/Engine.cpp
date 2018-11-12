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

    unsigned int id = 1;

    string player = "Alice";
    auto pair1 = make_pair(id,make_shared<Player>(false,player,id,make_shared<Bulbizarre>(id,WEST
            ,200,Position(3,9))));
    this->currentState.getPlayers().insert(pair1);
    unsigned int id2 = 0;
    string player2 = "Bob";
    auto pair2 =make_pair(id2,make_shared<Player>(Player(true,player2,id2,make_shared<Salameche>(id2,EST
            ,150,Position(20,20)))));
    this->currentState.getPlayers().insert(pair2);
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

