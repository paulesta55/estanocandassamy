//
// Created by paul on 27/10/18.
//

#include "Observable.h"
#include <algorithm>
#include <iostream>

using namespace std;
void state::Observable::registerObserver(Observer *o) {
    this->observers.push_back(o);
}

void state::Observable::unregisterObserver(state::Observer *o) {
    observers.erase(find(observers.cbegin(),observers.cend(),o));

}


state::Observable::~Observable() = default;

void state::Observable::unregisterObservers() {
    observers.clear();
}

void const state::Observable::notifyObservers(const state::Event &e) {
//    int c = 0;
    for (auto o : observers)
    {

//        cout << "obs notified" << c << endl;
        o->stateChanged(e);
//        cout << "command " << c << "completed" <<endl;
    }
//    cout << "end of observers" <<endl;
}
