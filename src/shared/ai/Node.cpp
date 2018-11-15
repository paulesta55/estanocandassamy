//
// Created by paul on 13/11/18.
//

#include "Node.h"
#include "state/Map.h"
#include <memory>
#include <iostream>
using namespace std;

const state::Position &ai::Node::getPosition() {
    return position;
}

std::vector<shared_ptr<ai::Node>> ai::Node::getAvailableNeigbors (uint authorizedTiles,state::Map* m){
    state::Position current = this->position;
    std::vector <std::shared_ptr<ai::Node>> list_Node;
    int positionInList = current.x + current.y * m->getWidth();
    std::vector <int> positionNeigbors = {(int)(positionInList-m->getWidth()),(int)(positionInList+m->getWidth()),(positionInList-1),(positionInList+1)};
    for (auto neighbor : positionNeigbors){
        if(m->getLayers()->at(0).getData()->at(static_cast<unsigned long>(neighbor)) == authorizedTiles){
            list_Node.push_back(make_shared<Node>(this, state::Position(neighbor%m->getWidth(),
                                                                        static_cast<unsigned int>((int)(neighbor / m->getWidth()))), this->cost + 1, 0));
        }
    }
    return list_Node;
}


ai::Node::Node(ai::Node *nPrevious, state::Position p, unsigned int cost, unsigned int heuristic):
        heuristic(heuristic),cost(cost),position(p),previousNode(nPrevious) {}

