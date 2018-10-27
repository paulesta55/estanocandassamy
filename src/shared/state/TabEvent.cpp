//
// Created by paul on 27/10/18.
//

#include "TabEvent.h"
#include <memory>
using namespace state;
using namespace std;
state::TabEvent::TabEvent(TabEventId te, unsigned int playerId) : tabEventId(te), playerId(playerId){}

const state::EventType state::TabEvent::getEventType() {
    return EventType ::TAB_EVENT;
}

state::Event *const state::TabEvent::clone() {

    shared_ptr<TabEvent> e_ptr;
    e_ptr.reset( new TabEvent(this->tabEventId,this->playerId));
    return e_ptr.get();
}
