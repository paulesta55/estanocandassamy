//
// Created by paul on 13/11/18.
//

#include "HCompare.h"
#include <state.h>
#include "Node.h"
using namespace std;
using namespace ai;
using namespace state;


bool ai::HCompare::operator()(shared_ptr<Node> n1, shared_ptr<Node> n2) {
    if(n1->heuristic < n2->heuristic)
        return true;
    if(n1->heuristic == n2->heuristic)
        return false;
    return new runtime_error("failed to sort in priority queue");
}

