#ifndef MICROFSM_H
#define MICROFSM_H

#define MAX_STATES 128
#define MAX_INPUTS 32
#define MIN_STATE_ID 1
#define MIN_INPUT_ID 1

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
  int inputs[MAX_INPUTS]; // Stores IDs of tracked inputs to the FSM

  // Stores ID's of destination states when the
  // FSM recieves a specific input from a specific source state. The states
  // and inputs arrays are PARALLEL with the transitions array; indexes must be
  // identical.
  int destinations[MAX_INPUTS][MAX_STATES];
} mfsm_fsm;

/***************************************
* FSM Interface Functions
***************************************/

// void initFSM (mfsm_fsm*)
//
// Set default values for an FSM.
//
// Parameters:
// fsm  mfsm_fsm  FSM context
//
// Returns:
// Nothing
void initFSM(mfsm_fsm *fsm);

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
int isValidInputID(mfsm_fsm fsm, int n);

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
int isValidTransition(mfsm_fsm fsm, int n, int s);

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
int addTransition(mfsm_fsm *fsm, int n, int s, int d);

// int removeTransition(struct mfsm_fsm*, int, int)
//
// Removes the transition from state s using input n.
//
// Parameters:
// fsm  mfsm_fsm* Pointer to FSM context
// n    int       Input ID
// s    int       Source state ID
//
// Returns:
// 0  -- Transition successfully removed
// -1 -- Invalid transition ID
// -2 -- Invalid source state ID
// -3 -- Something went wrong removing the transition destination
int removeTransition(mfsm_fsm *fsm, int n, int s);

// int removeTransitionAll(struct mfsm_fsm*, int)
//
// Removes all transitions using input n.
//
// Parameters:
// fsm  mfsm_fsm* Pointer to FSM context
// n    int       Input ID
//
// Returns:
// 0  -- Transition successfully removed
// -1 -- Invalid transition ID
// -2 -- Something went wrong removing the transition destinations
int removeTransitionAll(mfsm_fsm *fsm, int n);

// int addState(mfsm_fsm*, int)
//
// Adds a state ID to the list of tracked states.
//
// Parameters:
// fsm  mfsm_fsm* Pointer to FSM context
// s    int       State ID
//
// Returns:
// 0  -- State successfully created
// -1 -- State ID exceeded acceptable bounds (0 < s)
// -2 -- State ID already exists
// -3 -- The states array is full. No more states can be tracked at this time.
int addState(mfsm_fsm *fsm, int s);

// int removeState(mfsm_fsm*, int)
//
// Removes a state ID from the list of tracked states.
//
// Parameters:
// fsm  mfsm_fsm* Pointer to FSM context
// s    int       State ID
//
// Returns:
// 0  -- State successfully removed
// -1 -- State could not be found
int removeState(mfsm_fsm *fsm, int s);

// int addInput(mfsm_fsm*, int)
//
// Adds an input ID to the list of tracked inputs.
//
// Parameters:
// fsm  mfsm_fsm* Pointer to FSM context
// s    int       Input ID
//
// Returns:
// 0  -- Input successfully created
// -1 -- Input ID exceeded acceptable bounds (0 < n)
// -2 -- Input ID already exists
// -3 -- The inputs array is full. No more inputs can be tracked at this time.
int addInput(mfsm_fsm *fsm, int n);

// int removeInput(mfsm_fsm*, int)
//
// Removes a input ID from the list of tracked inputs.
//
// Parameters:
// fsm  mfsm_fsm* Pointer to FSM context
// s    int       Input ID
//
// Returns:
// 0  -- Input successfully removed
// -1 -- Input could not be found
int removeInput(mfsm_fsm *fsm, int n);


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
int getInputIndex(mfsm_fsm fsm, int n);

#endif //MICROFSM_H
