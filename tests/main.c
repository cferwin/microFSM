#include "test.h"
#include "microFSM.h"

// Utility function tests

void test_getStateIndex(void) {
  // Create a mock fsm and state
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.states[4] = 7;

  // Attempt to get the correct index
  int i = getStateIndex(fsm, 7);
  assertMsg(i == 4, "The returned state index was incorrect");

  report("getStateIndex()");
}

void test_getInputIndex(void) {
  // Create a mock fsm and input
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.inputs[4] = 7;

  // Attempt to get the correct index
  int i = getInputIndex(fsm, 7);
  assertMsg(i == 4, "The returned input index was incorrect");

  report("getInputIndex()");
}

// FSM Interface function tests

void test_isValidStateID(void) {
  // Create a mock fsm and state
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.states[4] = 7;

  // Attempt to verify the transition
  int i = isValidStateID(fsm, 7);
  assertMsg(i == 0, "The state was considered invalid");

  report("isValidStateID()");
}

void test_isValidInputID(void) {
  // Create a mock fsm and input
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.inputs[4] = 7;

  // Attempt to verify the input ID
  int i = isValidInputID(fsm, 7);
  assertMsg(i == 0, "The input was considered invalid");

  report("isValidInputID()");
}

void test_isValidTransition(void) {
  // Create a mock fsm, input, source state, and destination state
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.inputs[4] = 7;            // Input
  fsm.states[9] = 2;            // Source state
  fsm.states[8] = 6;            // Destination state
  fsm.destinations[4][9] = 6;   // Make the associations

  // Attempt to verify the transition
  int i = isValidTransition(fsm, 7, 2);
  assertMsg(i == 0, "The transition was considered invalid");
  if (i != 0) {
    printf("Returned: %d\n", i);
  }

  report("isValidTransition()");
}

void test_addState(void) {
  // Create a mock fsm
  mfsm_fsm fsm;
  initFSM(&fsm);

  // Attempt to add a new state ID
  int i = addState(&fsm, 7);
  assertMsg(i == 0, "The state ID could not be added");
  if (i != 0) {
    printf("Returned: %d\n", i);
  }

  report("addState()");
}

void test_removeState(void) {
  // Create a mock fsm and state
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.states[4] = 7;

  // Attempt to remove a state
  int i = removeState(&fsm, 7);
  assertMsg(i == 0, "The state ID could not be removed");
  if (i != 0) {
    printf("Returned: %d\n", i);
  } else {
    assertMsg(fsm.states[4] < MIN_STATE_ID, "Index was not reset after  supposed removal");
  }

  report("removeState()");
}

void test_addInput(void) {
  // Create a mock fsm
  mfsm_fsm fsm;
  initFSM(&fsm);

  // Attempt to add a new input ID
  int i = addInput(&fsm, 7);
  assertMsg(i == 0, "The input ID could not be added");
  if (i != 0) {
    printf("Returned: %d\n", i);
  }

  report("addInput()");
}

void test_removeInput(void) {
  // Create a mock fsm and input
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.inputs[4] = 7;

  // Attempt to remove an input
  int i = removeInput(&fsm, 7);
  assertMsg(i == 0, "The input ID could not be removed");
  if (i != 0) {
    printf("Returned: %d\n", i);
  } else {
    assertMsg(fsm.inputs[4] < MIN_INPUT_ID, "Index was not reset after  supposed removal");
  }

  report("removeInput()");
}

void test_addTransition(void) {
  // Create a mock fsm, input, source state, and destination state
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.inputs[4] = 7;            // Input
  fsm.states[9] = 2;            // Source state
  fsm.states[8] = 6;            // Destination state

  // Attempt to create the transition
  int i = addTransition(&fsm, 7, 2, 6);
  assertMsg(i == 0, "The transition was not successfully created");
  if (i != 0) {
    printf("Returned: %d\n", i);
  }

  // Test whether the transition is stored in the destinations array
  int d = fsm.destinations[4][9];
  assertMsg(d == 6, "The stored destination ID was incorrect");
  if (d != 6) {
    printf("Value: %d\n", d);
  }

  report("addTransition()");
}

void test_removeTransition(void) {
  // Create a mock fsm, input, source state, and destination state
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.inputs[4] = 7;            // Input
  fsm.states[9] = 2;            // Source state
  fsm.states[8] = 6;            // Destination state

  // Attempt to create the transition
  int i = addTransition(&fsm, 7, 2, 6);
  assertMsg(i == 0, "The transition was not successfully created");
  if (i != 0) {
    printf("Returned: %d\n", i);
  }
  
  // Attempt to remove the transition
  i = removeTransition(&fsm, 7, 2);
  assertMsg(i == 0, "The transition was not successfully removed");
  if (i != 0) {
    printf("Returned: %d\n", i);
  }

  // Test whether the transition was removed from the destinations array
  int d = isValidStateID(fsm, fsm.destinations[4][9]);
  assertMsg(d != 0, "The stored destination ID was still valid");

  report("removeTransition()");
}

void test_removeTransitionAll(void) {
  // Create a mock fsm, inputs, source states, and destination states
  mfsm_fsm fsm;
  initFSM(&fsm);

  // Input
  fsm.inputs[3] = 7;

  // Source states
  fsm.states[2] = 1;
  fsm.states[4] = 2;
  fsm.states[6] = 3;

  // Destination states
  fsm.states[1] = 4;
  fsm.states[3] = 5;
  fsm.states[5] = 6;

  // Create the transitions
  addTransition(&fsm, 7, 1, 4);
  addTransition(&fsm, 7, 2, 5);
  addTransition(&fsm, 7, 3, 6);
  
  // Attempt to remove the transitions
  int i = removeTransitionAll(&fsm, 7);
  assertMsg(i == 0, "The transitions were not successfully removed");
  if (i != 0) {
    printf("Returned: %d\n", i);
  }

  // Test whether the transitions were removed from the destinations array
  int d = isValidStateID(fsm, fsm.destinations[3][2]);
  assertMsg(d != 0, "The stored destination ID #1 was still valid");

  d = isValidStateID(fsm, fsm.destinations[3][4]);
  assertMsg(d != 0, "The stored destination ID #2 was still valid");

  d = isValidStateID(fsm, fsm.destinations[3][6]);
  assertMsg(d != 0, "The stored destination ID #3 was still valid");

  report("removeTransitionAll()");
}

void test_doTransition(void) {
  // Create a mock fsm, input, source state, and destination state
  mfsm_fsm fsm;
  initFSM(&fsm);
  fsm.inputs[4] = 7;            // Input
  fsm.states[9] = 2;            // Source state
  fsm.states[8] = 6;            // Destination state
  fsm.curState = 2;

  // Attempt to create the transition
  int i = addTransition(&fsm, 7, 2, 6);
  assertMsg(i == 0, "The transition was not successfully created");
  if (i != 0) {
    printf("Returned: %d\n", i);
  }
  
  // Attempt to execute the transition
  i = doTransition(&fsm, 7);
  assertMsg(i > MIN_STATE_ID, "The transition was not successful");
  if (i < 0) {
    printf("Returned: %d\n", i);
  }

  // Test whether the current state is valid
  int d = isValidStateID(fsm, fsm.curState);
  assertMsg(d == 0, "The current state ID was invalid");

  // Test whether the current state has been updated
  assertMsg(fsm.curState == 6, "The current state ID was not changed");

  report("doTransition()");
}


int main(int argc, char **argv) {
  printf("Running tests...\n\n");
  
  // Test utility functions
  test_getStateIndex();
  test_getInputIndex();

  // Test validators
  test_isValidStateID();
  test_isValidInputID();
  test_isValidTransition();

  // Test state addition/removal
  test_addState();
  test_removeState();

  // Test input addition/removal
  test_addInput();
  test_removeInput();

  // Test transition addition/removal
  test_addTransition();
  test_removeTransition();
  test_removeTransitionAll();

  // Test transition functionality
  test_doTransition();

  return 0;
}
