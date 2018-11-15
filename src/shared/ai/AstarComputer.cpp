//
// Created by paul on 13/11/18.
//
#include <memory>
#include "AstarComputer.h"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <iostream>
using namespace std;
using namespace state;
using namespace ai;


shared_ptr<Node> AstarComputer::compute() {
    openList.push_back(source);
    int k = 0;

    while(!openList.empty())
    {


        shared_ptr<Node> n;
        n = openList.front();
        openList.erase(openList.begin());
        openList.shrink_to_fit();
        cout << k << " iterations" << endl;

        cout << "position :"<<n->getPosition().x << ","<< n->getPosition().y << endl;
        if(n->getPosition().x == objectif->getPosition().x && n->getPosition().y == objectif->getPosition().y)
            return n;
        else {
            for(const auto &v : n->getAvailableNeigbors(35,map.get())){
                bool passInFor = true;
                //looking for v in closedList with heuristique < current heuristique
                for(auto ni:closedList)
                {
                    // if found don't insert in openList ...
                    if(ni->getPosition().x == v->getPosition().x && ni->getPosition().y == v->getPosition().y && ni->heuristic < v->heuristic)
                    {
                        passInFor = false;
                    }
                }
                // don't need to check if v is in openlist if v is already found in closedList with heuristique < current heuristique
                if(passInFor)
                {
                    // same than for closedList
                    for(auto ni: openList)
                    {
                        if(ni->getPosition().x == v->getPosition().x && ni->getPosition().y == v->getPosition().y && ni->heuristic < v->heuristic)
                        {
                            passInFor = false;
                        }
                    }
                }
                if(passInFor) {
                    v->cost += n->cost+1;
                    v->heuristic = static_cast<unsigned int>(v->cost + std::sqrt(((int)(objectif->getPosition().x) - (int)(v->getPosition().x)) * ((int)
                                                (objectif->getPosition().x) - (int)(v->getPosition().x)) +((int)(objectif->getPosition().y)-
                                                        (int)(v->getPosition().y))*((int)(objectif->getPosition().y)-(int)(v->getPosition().y))));
                    openList.push_back(v);
                    std::sort(openList.begin(),openList.end(),HCompare());
                }
            }
            
        }
        k = k+1;
        closedList.push_back(n);

    }

    return nullptr;
}

AstarComputer::AstarComputer(shared_ptr<state::Map> map, Node &objectif, Node &source) {
    this->objectif = make_shared<Node>(objectif);
    this->source = make_shared<Node>(source);
    this->map = map;
}

