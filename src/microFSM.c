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

// int isValidInputID(struct mfsm_fsm, int)
//
// Ensures the input ID is present in the FSM.
//
// Parameters:
// fsm  mfsm_fsm  FSM context
// n    int       Input ID
//
// Returns:
// 0        -- Valid input ID
// Non-Zero -- Invalid input ID
int isValidInputID(mfsm_fsm fsm, int n) {
  int i = 0;
  for (; i < MAX_INPUTS; i++) {
    if (fsm.inputs[i] == n) {
      return 0;
    }
  }

  return -1;
}

// int isValidTransition(struct mfsm_fsm, int, int)
//
// Verifies the presence of a transition from state s with input n.
//
// Parameters:
// fsm        mfsm_fsm  FSM context
// n          int       Input ID
// s          int       Source state ID
//
// Returns:
// 0  -- Valid transition
// -1 -- Invalid input
// -2 -- Invalid source state
// -3 -- Transition has invalid destination state ID
int isValidTransition(mfsm_fsm fsm, int n, int s) {
  // Find the given input
  int ni = getInputIndex(fsm, n);
  if (ni == -1) {
    return -1;
  }

  // Find the given source state
  int si = getStateIndex(fsm, s);
  if (si == -1) {
    return -2;
  }

  // Validate the transition's destination state
  if (isValidStateID(fsm, fsm.destinations[ni][si]) != 0) {
    return -3;
  }

  // Input ID, source state ID, and destination state IDs are all valid
  return 0;
}

// int addTransition(struct mfsm_fsm, int, int, int)
//
// Creates a transition from State s with Input n to State d.
//
// Parameters:
// fsm        mfsm_fsm* Pointer to FSM context
// n          int       Input ID
// s          int       Source state ID
// d          int       Destination state ID
//
// Returns:
// 0  -- Transition successfully created
// -1 -- Invalid transition ID
// -2 -- Invalid source state ID
// -3 -- Invalid destination state ID
// -4 -- Something went wrong associating the transition and states
int addTransition(mfsm_fsm *fsm, int n, int s, int d) {
  // Find the given input
  int ni = getInputIndex(*fsm, n);
  if (ni == -1) {
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

  // Associate the input and source state with the destination state
  fsm->destinations[ni][si] = d;

  // Confirm the transition's destination state was set correctly
  if (isValidTransition(*fsm, n, s) != 0) {
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

// int getInputIndex(struct mfsm_fsm, int)
//
// Finds the index of the given input in the inputs array.
//
// Parameters:
// fsm  mfsm_fsm  FSM context
// n    int       Input ID 
//
// Returns:
// Success -- Index of the given input
// Failure -- -1
int getInputIndex(mfsm_fsm fsm, int n) {
  int i = 0;
  for (; i < MAX_INPUTS; i++) {
    if (fsm.inputs[i] == n) {
      return i;
    }
  }

  return -1;
}
