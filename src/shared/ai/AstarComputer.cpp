//
// Created by paul on 13/11/18.
//
#include <memory>
#include "AstarComputer.h"
#include <algorithm>
#include <cmath>
#include <iterator>
using namespace std;
using namespace state;
using namespace ai;


shared_ptr<Node> AstarComputer::compute() {
    openList.push_back(source);
    while(!openList.empty())
    {
        shared_ptr<Node> n;
        n.reset(openList.front().get());

        openList.pop_front();


        if(n->getPosition().x == objectif->getPosition().x && n->getPosition().y == objectif->getPosition().y)
            return n;
        else {
            for(auto v : n->getAvailableNeigbors(35,map.get())){
                if(std::find(closedList.begin(),closedList.end(),v)==closedList.end() ||
                std::find(openList.begin(),openList.end(),v)==openList.end()) {
                    v->heuristic = static_cast<unsigned int>(v->cost + std::sqrt(((int)(objectif->getPosition().x) - (int)(v->getPosition().x)) * ((int)
                                                (objectif->getPosition().x) - (int)(v->getPosition().x)) +((int)(objectif->getPosition().y)-
                                                        (int)(v->getPosition().y))*((int)(objectif->getPosition().y)-(int)(v->getPosition().y))));
                    openList.push_back(v);
                    std::sort(openList.begin(),openList.end(),HCompare());
                }
            }
            
        }
    }

    return nullptr;
}

AstarComputer::AstarComputer(state::Map &map, Node &objectif, Node &source) {
    this->objectif = make_shared<Node>(objectif);
    this->source = make_shared<Node>(source);
//    this->map.reset(map);
}

