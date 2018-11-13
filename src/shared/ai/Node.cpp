//
// Created by paul on 13/11/18.
//

#include "Node.h"

const state::Position &ai::Node::getPosition() {
    return position;
}

ai::Node::Node(ai::Node *nPrevious, state::Position p, unsigned int cost, unsigned int heuristic):previousNode(nPrevious),position(p),cost(cost),heuristic(heuristic) {}

