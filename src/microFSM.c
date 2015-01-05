#include "microFSM.h"

/***************************************
* Utility Functions
**************************************/

// int getStateIndex(struct mfsm_fsm, int)
//
// Finds the index of the given state in the states array.
//
// Parameters:
// fsm        mfsm_fsm  FSM context
// src        int       State ID
//
// Returns:
// Success -- Index of the given state
// Failure -- -1
int getStateIndex(mfsm_fsm fsm, int state) {
  int i = 0;
  for (; i < MAX_STATES; i++) {
    if (fsm.states[i] == state) {
      return i;
    }
  }

  return -1;
}

// int getTransitionIndex(struct mfsm_fsm, int)
//
// Finds the index of the given transition in the transitions array.
//
// Parameters:
// fsm      mfsm_fsm  FSM context
// trans    int       Transition ID 
//
// Returns:
// Success -- Index of the given transition
// Failure -- -1
int getTransitionIndex(mfsm_fsm fsm, int trans) {
  int i = 0;
  for (; i < MAX_STATES; i++) {
    if (fsm.transitions[i] == trans) {
      return i;
    }
  }

  return -1;
}
