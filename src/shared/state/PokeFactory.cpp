//
// Created by paul on 28/09/18.
//

#include "state.h"
#include "PokeFactory.h"
#include "Pokedata.h"
#include "Pokemon.h"

using namespace state;
using namespace std;

PokeFactory::PokeFactory() {
    vector<string> salaSkills;
    salaSkills.push_back("flameche");
    auto *saladata = new Pokedata(100,"feu",salaSkills,0);

    this->pokedataMap.insert(make_pair("salameche",saladata));
}

Pokemon* PokeFactory::buildPokemon(std::string name) {
    vector<int> position;
    position.push_back(0);
    position.push_back(0);

    auto *pokemon = new Pokemon(position,(int)this->pokedataMap[name]->getFullLife(),name);
    pokemon->pokedata = this->pokedataMap[name];
    return pokemon;
}