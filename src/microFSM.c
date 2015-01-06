#include "microFSM.h"

/***************************************
* FSM Interface Functions
***************************************/

// int isValidStateID(struct mfsm_fsm, int)
//
// Ensures the state ID is present in the FSM.
//
// Parameters:
// fsm        mfsm_fsm  FSM context
// s          int       State ID
//
// Returns:
// 0        -- Valid state ID
// Non-Zero -- Invalid state ID
int isValidStateID(mfsm_fsm fsm, int s) {
  int i = 0;
  for (; i < MAX_STATES; i++) {
    if (fsm.states[i] == s) {
      return 0;
    }
  }

  return -1;
}

// int isValidTransitionID(struct mfsm_fsm, int)
//
// Ensures the transition ID is present in the FSM.
//
// Parameters:
// fsm        mfsm_fsm  FSM context
// src        int       Transition ID
//
// Returns:
// 0        -- Valid transition ID
// Non-Zero -- Invalid transition ID
int isValidTransitionID(mfsm_fsm fsm, int t) {
  int i = 0;
  for (; i < MAX_TRANSITIONS; i++) {
    if (fsm.transitions[i] == t) {
      return 0;
    }
  }

  return -1;
}

// int isValidTransition(struct mfsm_fsm, int, int)
//
// Verifies the presence of a transition from src with transition trans.
//
// Parameters:
// fsm        mfsm_fsm  FSM context
// t          int       Transition ID
// s          int       Source state ID
//
// Returns:
// 0  -- Valid transition
// -1 -- Invalid transition
// -2 -- Invalid source state
// -3 -- Transition has invalid destination state ID
int isValidTransition(mfsm_fsm fsm, int t, int s) {
  // Find the given transition
  int ti = getTransitionIndex(fsm, t);
  if (ti == -1) {
    return -1;
  }

  // Find the given source state
  int si = getStateIndex(fsm, s);
  if (si == -1) {
    return -2;
  }

  // Validate the transition's destination state
  if (isValidStateID(fsm, fsm.destinations[ti][si]) != 0) {
    return -3;
  }

  // Transition ID, source state ID, and destination state IDs are all valid
  return 0;
}

// int addTransition(struct mfsm_fsm, int, int, int)
//
// Creates a transition from State s with Transition t to State d.
//
// Parameters:
// fsm        mfsm_fsm  FSM context
// t          int       Transition ID
// s          int       Source state ID
// d          int       Destination state ID
//
// Returns:
// 0  -- Transition successfully created
// -1 -- Invalid transition ID
// -2 -- Invalid source state ID
// -3 -- Invalid destination state ID
// -4 -- Something went wrong associating the transition and states
int addTransition(mfsm_fsm *fsm, int t, int s, int d) {
  // Find the given transition
  int ti = getTransitionIndex(*fsm, t);
  if (ti == -1) {
    return -1;
  }

  // Find the given source state
  int si = getStateIndex(*fsm, s);
  if (si == -1) {
    return -2;
  }

  // Confirm the destination state exists
  if (isValidStateID(*fsm, d) == -1) {
    return -3;
  }

  // Association the transition and source state with the destination state
  fsm->destinations[ti][si] = d;

  // Confirm the transition's destination state was set correctly
  if (isValidTransition(*fsm, t, s) != 0) {
    return -4;
  }

  return 0;
}


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
  for (; i < MAX_TRANSITIONS; i++) {
    if (fsm.transitions[i] == trans) {
      return i;
    }
  }

  return -1;
}
