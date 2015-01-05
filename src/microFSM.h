#ifndef MICROFSM_H
#define MICROFSM_H

#define MAX_STATES 128
#define MAX_TRANS 32

/***************************************
 * MicroFSM
 *
 * A small library to provide logic for modeling Finite State Machines. The
 * user may define the nature of states, transitions, and the topology of the
 * FSM. All the library requires is an ID to track the states and
 * transitions.
**************************************/

typedef struct mfsm_fsm {
  // ID of the currently active state. Used as the "source" state in
  // transitions.
  int curState;
  int states[MAX_STATES]; // Stores IDs of states tracked within the FSM
  int transitions[MAX_TRANS]; // Stores ID's of tracked transitions
  // Stores transition destinations associated with a specific transition ID
  // and source state. The states and transitions arrays are PARALLEL with
  // the destinations array; indexes must be identical.
  int destinations[MAX_TRANS][MAX_STATES];
} mfsm_fsm;

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
int getStateIndex(mfsm_fsm fsm, int state);

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
int getTransitionIndex(mfsm_fsm fsm, int trans);

#endif //MICROFSM_H
