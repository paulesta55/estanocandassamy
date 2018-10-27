//
// Created by paul on 27/10/18.
//

#include "Observable.h"
#include <algorithm>
using namespace std;
void state::Observable::registerObserver(Observer *o) {
    this->observers.push_back(o);
}

void state::Observable::unregisterObserver(state::Observer *o) {
    observers.erase(find(observers.cbegin(),observers.cend(),o));

}


state::Observable::~Observable() {

}

void state::Observable::unregisterObservers() {
    observers.clear();
}

void const state::Observable::notifyObservers(const state::Event &e) {
    for (auto o : observers)
    {
        o->stateChanged(e);
    }
}
