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

int main(int argc, char **argv) {
  printf("Running tests...\n\n");
  
  // Test utility functions
  test_getStateIndex();
  test_getTransitionIndex();

  return 0;
}
