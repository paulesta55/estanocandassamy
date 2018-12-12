#include "PreviousState.h"
#include <memory>
using namespace engine;

PreviousState::PreviousState(state::Orientation pOrientation, unsigned int pId, state::Position previousP, unsigned int previousLife, ActionType aType) : previousO(pOrientation),playerId(pId),previousP(previousP),previousLife(previousLife),aType(aType)
{
}
