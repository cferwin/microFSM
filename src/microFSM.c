#include "microFSM.h"

// An event ID which represents an invalid Event as per documentation.
#define NULL_EVENT_ID -1

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
void initFSM(mfsm_fsm *fsm) {
  int i = 0;
  int j = 0;
  fsm->curState = 0;

  // States array
  for(; i < MAX_STATES; i++) {
    fsm->states[i] = 0;
  }

  // Inputs array
  for(i = 0; i < MAX_INPUTS; i++) {
    fsm->inputs[i] = 0;
  }

  // Destinations array
  for(i = 0; i < MAX_INPUTS; i++) {
    for(j = 0; j < MAX_STATES; j++) {
      fsm->destinations[i][j].dest = 0;
      initEvent(&fsm->destinations[i][j].outputEvent, NULL_EVENT_ID);
    }
  }

  // Event Queue
  initEventQueue(&fsm->eq);
}

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
  // Confirm the ID is above the minimum
  if (s < MIN_STATE_ID) {
    return -1;
  }

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
  // Confirm the ID is above the minimum
  if (n < MIN_INPUT_ID) {
    return -1;
  }

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
  if (isValidStateID(fsm, fsm.destinations[ni][si].dest) != 0) {
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
  mfsm_Transition *transition = &fsm->destinations[ni][si];
  transition->dest = d;
  initEvent(&transition->outputEvent, NULL_EVENT_ID);

  // Confirm the transition's destination state was set correctly
  if (isValidTransition(*fsm, n, s) != 0) {
    return -4;
  }

  return 0;
}

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
int removeTransition(mfsm_fsm *fsm, int n, int s) {
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

  // Reset the destination ID for the state/input transition
  fsm->destinations[ni][si].dest = MIN_STATE_ID-1;

  // Confirm the transition's destination state was reset and is invalid
  if (isValidTransition(*fsm, n, s) == 0) {
    return -3;
  }

  return 0;
}

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
int removeTransitionAll(mfsm_fsm *fsm, int n) {
  // Find the given input
  int ni = getInputIndex(*fsm, n);
  if (ni == -1) {
    return -1;
  }

  // Reset the all destination IDs for the transition input
  int i = 0;
  for (; i < MAX_STATES; i++) {
    // Reset the destination
    fsm->destinations[ni][i].dest = MIN_STATE_ID-1;

    // Confirm the transition's destination state was reset and is invalid
    if (isValidTransition(*fsm, n, fsm->states[i]) == 0) {
      return -2;
    }
  }

  return 0;
}

// int setTransitionOutput(mfsm_fsm*, int, int, mfsm_Event)
//
// Set an Event to be sent out to all listeners when the transition is
// executed.
//
// Parameters:
// fsm  mfsm_fsm* Pointer to FSM context
// n    int       Input ID
// s    int       Source state ID
//
// Returns:
// Success -- 0
// Failure:
//  -1 -- Invalid input ID
//  -2 -- Invalid source state ID
//  -3 -- Something went wrong setting the event
int setTransitionOutput(mfsm_fsm *fsm, int n, int s, mfsm_Event e) {
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

  // Copy the Event into the Transition
  // TODO: This must be updated if the Event struct is changed.
  // This may indicate the need for a copy function for Events.
  initEvent(&fsm->destinations[ni][si].outputEvent, e.id);

  if (fsm->destinations[ni][si].outputEvent.id != e.id) {
    return -3;
  }

  return 0;
}

// int clearTransitionOutput(mfsm_fsm*, int, int)
//
// Reset the transition's output Event. An Event will no longer be sent for
// this transition.
//
// Parameters:
// fsm  mfsm_fsm* Pointer to FSM context
// n    int       Input ID
// s    int       Source state ID
//
// Returns:
// Success -- 0
// Failure:
//  -1 -- Invalid input ID
//  -2 -- Invalid source state ID
//  -3 -- Something went wrong resetting the event
int clearTransitionOutput(mfsm_fsm *fsm, int n, int s) {
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

  // Invalidate the output event
  initEvent(&fsm->destinations[ni][si].outputEvent, NULL_EVENT_ID);

  if (fsm->destinations[ni][si].outputEvent.id != NULL_EVENT_ID) {
    return -3;
  }

  return 0;
}

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
// -1 -- State ID exceeded acceptable bounds (MIN_STATE_ID < s)
// -2 -- State ID already exists
// -3 -- The states array is full. No more states can be tracked at this time.
int addState(mfsm_fsm *fsm, int s) {
  // Boundary check for state ID
  if (s < MIN_STATE_ID) {
    return -1;
  }

  // Ensure the state is not already being tracked
  if (getStateIndex(*fsm, s) != -1) {
    return -2;
  }

  // Insert the state ID into the first free space in the states array
  int i = 0;
  for (; i < MAX_STATES; i++) {
    if (fsm->states[i] < MIN_STATE_ID) {
      fsm->states[i] = s;
      return 0;
    }
  }

  // A free space could not be found for the ID.
  return -3;
}

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
int removeState(mfsm_fsm *fsm, int s) {
  // Find the index of the state ID
  int si = getStateIndex(*fsm, s);
  if (si == -1) {
    return -1;
  }

  // Reset the index to an invalid ID so it can be reused
  fsm->states[si] = MIN_STATE_ID-1;
  
  return 0;
}

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
int addInput(mfsm_fsm *fsm, int n) {
  // Boundary check for input ID
  if (n < MIN_INPUT_ID) {
    return -1;
  }

  // Ensure the input is not already being tracked
  if (getInputIndex(*fsm, n) != -1) {
    return -2;
  }

  // Insert the input ID into the first free space in the inputs array
  int i = 0;
  for (; i < MAX_INPUTS; i++) {
    if (fsm->inputs[i] < MIN_INPUT_ID) {
      fsm->inputs[i] = n;
      return 0;
    }
  }

  // A free space could not be found for the ID.
  return -3;
}

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
int removeInput(mfsm_fsm *fsm, int n) {
  // Find the index of the input ID
  int ni = getInputIndex(*fsm, n);
  if (ni == -1) {
    return -1;
  }

  // Reset the index to an invalid ID so it can be reused
  fsm->inputs[ni] = MIN_INPUT_ID-1;
  
  return 0;
}


// int doTransition(struct mfsm_fsm*, int)
//
// Executes the transition from the FSM's current state using input n. Returns
// the new current state's ID or an error code.
//
// Parameters:
// fsm  mfsm_fsm  FSM context
// n    int       Input ID 
//
// Returns:
// Success -- ID of new current State
// Failure:
//  -1 -- Invalid input ID
//  -2 -- The current state ID is invalid
int doTransition(mfsm_fsm *fsm, int n) {
  // Find the given input
  int ni = getInputIndex(*fsm, n);
  if (ni == -1) {
    return -1;
  }

  // Find the current source state
  int si = getStateIndex(*fsm, fsm->curState);
  if (si == -1) {
    return -2;
  }

  // Check if there is a new destination for the transition
  if (isValidTransition(*fsm, n, fsm->curState) == 0) {
    fsm->curState = fsm->destinations[ni][si].dest;
  }

  // Try to fire the output event
  if (fsm->destinations[ni][si].outputEvent.id != NULL_EVENT_ID) {
    sendEvent(fsm->eq, fsm->destinations[ni][si].outputEvent);
  }

  return fsm->curState;
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
  if (isValidStateID(fsm, state) != 0) {
    return -1;
  }

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
  if (isValidInputID(fsm, n) != 0) {
    return -1;
  }

  int i = 0;
  for (; i < MAX_INPUTS; i++) {
    if (fsm.inputs[i] == n) {
      return i;
    }
  }

  return -1;
}
