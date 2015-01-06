#ifndef MICROFSM_H
#define MICROFSM_H

#define MAX_STATES 128
#define MAX_TRANSITIONS 32

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
  int transitions[MAX_TRANSITIONS]; // Stores ID's of tracked transitions
  // Stores transition destinations associated with a specific transition ID
  // and source state. The states and transitions arrays are PARALLEL with
  // the destinations array; indexes must be identical.
  int destinations[MAX_TRANSITIONS][MAX_STATES];
} mfsm_fsm;

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
int isValidStateID(mfsm_fsm fsm, int s);

// int isValidTransitionID(struct mfsm_fsm, int)
//
// Ensures the transition ID is present in the FSM.
//
// Parameters:
// fsm        mfsm_fsm  FSM context
// t        int       Transition ID
//
// Returns:
// 0        -- Valid transition ID
// Non-Zero -- Invalid transition ID
int isValidTransitionID(mfsm_fsm fsm, int t);

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
int isValidTransition(mfsm_fsm fsm, int t, int s);

// int addTransition(struct mfsm_fsm, int, int, int)
//
// Creates a transition from State s with Transition t to State d.
//
// Parameters:
// fsm        mfsm_fsm* Pointer to FSM context
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
int addTransition(mfsm_fsm *fsm, int t, int s, int d);


/***************************************
* Utility Functions
***************************************/

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
