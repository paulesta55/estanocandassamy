//
// Created by paul on 28/10/18.
//
#include "StateEvent.h"
#include "state.h"
using namespace state;
using namespace std;

StateEvent::StateEvent(StateEventId se) : stateEvent(se){}

EventType StateEvent::getEventType() const {
    return STATE_EVENT;
}

Event *StateEvent::clone() const {


    return new StateEvent(*this);
}
