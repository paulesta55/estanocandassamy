//
// Created by paul on 13/11/18.
//
#include <memory>
#include "AstarComputer.h"

using namespace std;
using namespace state;
using namespace ai;


Node *AstarComputer::compute() {
    openList.push(source.get());
    while(!openList.empty())
    {
        unique_ptr<Node> n;
        n.reset(openList.top());
        if(n->getPosition().x == objectif->getPosition().x && n->getPosition().y == objectif->getPosition().y)
            return n.get();
        else {
            // traitement...
        }
    }

    return nullptr;
}

AstarComputer::AstarComputer(state::Map &map, Node &objectif, Node &source) {
    this->objectif = make_shared<Node>(objectif);
    this->source = make_shared<Node>(source);
}

