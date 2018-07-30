#include "states.h"

///GameState
void state::change(GameState*& state) {
    if(state->mNext)
        state = state->mNext;
}
