#include "test.h"
#include "microFSM.h"

// Utility function tests

void test_getStateIndex(void) {
  // Create a mock fsm and state
  mfsm_fsm fsm;
  fsm.states[4] = 7;

  // Attempt to get the correct index
  int i = getStateIndex(fsm, 7);
  assertMsg(i == 4, "The returned state index was incorrect");

  report("getStateIndex()");
}

void test_getTransitionIndex(void) {
  // Create a mock fsm and transition
  mfsm_fsm fsm;
  fsm.transitions[4] = 7;

  // Attempt to get the correct index
  int i = getTransitionIndex(fsm, 7);
  assertMsg(i == 4, "The returned transition index was incorrect");

  report("getTransitionIndex()");
}

// FSM Interface function tests

void test_isValidStateID(void) {
  // Create a mock fsm and state
  mfsm_fsm fsm;
  fsm.states[4] = 7;

  // Attempt to verify the transition
  int i = isValidStateID(fsm, 7);
  assertMsg(i == 0, "The state was considered invalid");

  report("isValidStateID()");
}

void test_isValidTransitionID(void) {
  // Create a mock fsm and transition
  mfsm_fsm fsm;
  fsm.transitions[4] = 7;

  // Attempt to verify the transition
  int i = isValidTransitionID(fsm, 7);
  assertMsg(i == 0, "The transition was considered invalid");

  report("isValidTransitionID()");
}


int main(int argc, char **argv) {
  printf("Running tests...\n\n");
  
  // Test utility functions
  test_getStateIndex();
  test_getTransitionIndex();

  // Test FSM interface functions
  test_isValidStateID();
  test_isValidTransitionID();

  return 0;
}
