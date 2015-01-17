#include "test.h"
#include "microFSM.h"
#include "event.h"

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


/****************************************
* Test Event System
****************************************/
void test_initEvent(void) {
  // Initialize an event
  mfsm_Event e;
  initEvent(&e, 7);

  // Test if it was properly initialized
  assertMsg(e.id == 7, "Event ID was not properly initialized");
  if (e.id != 7) {
    printf("Value: %d\n", e.id);
  }

  report("initEvent()");
}

void test_appendEvent(void) {
  // Create some Events and an EventListener
  mfsm_Event e1;
  mfsm_Event e2;
  initEvent(&e1, 7);
  initEvent(&e2, 9);

  mfsm_EventListener el;
  initEventListener(&el);

  // Add the event to the listener
  appendEvent(&el, e1);
  appendEvent(&el, e2);

  // Test if the events were added to the queue.
  assertMsg(el.events[0].id == 7, "Event #1 was not successfully appended");
  assertMsg(el.numEvents == 1, "numEvents was not updated");
  assertMsg(el.events[1].id == 9, "Event #2 was not successfully appended");
  assertMsg(el.numEvents == 2, "numEvents was not updated");

  report("appendEvent()");
}

void test_getNextEvent(void) {
  // Create some Events and an EventListener
  mfsm_Event e1;
  mfsm_Event e2;
  initEvent(&e1, 7);
  initEvent(&e2, 9);

  mfsm_EventListener el;
  initEventListener(&el);

  // Add the event to the listener
  appendEvent(&el, e1);
  appendEvent(&el, e2);

  // Test if the events were added to the queue.
  assertMsg(el.events[0].id == 7, "Event #1 was not successfully appended");
  assertMsg(el.numEvents == 1, "numEvents was not updated");
  assertMsg(el.events[1].id == 9, "Event #2 was not successfully appended");
  assertMsg(el.numEvents == 2, "numEvents was not updated");

  // Try to retrieve the events and retest them
  mfsm_Event d;
  getNextEvent(&el, &d);
  assertMsg(d.id == 9, "Event #2 was not successfully retrieved");
  assertMsg(el.numEvents == 1, "numEvents was not updated");

  getNextEvent(&el, &d);
  assertMsg(d.id == 7, "Event #1 was not successfully retrieved");
  assertMsg(el.numEvents == 0, "numEvents was not updated");

  report("getNextEvent()");
}

void test_initEventQueue(void) {
  // Initialize an EventQueue
  mfsm_EventQueue eq;
  initEventQueue(&eq);

  // Test if it was properly initialized
  assertMsg(eq.numListeners == 0, "EventQueue was not properly initialized");
  if (eq.numListeners != 0) {
    printf("Value: %d\n", eq.numListeners);
  }

  assertMsg(eq.listeners[3] == 0, "EventQueue was not properly initialized");
  if (eq.listeners[3] != 0) {
    printf("Value: %p\n", eq.listeners[3]);
  }

  report("initEventQueue()");
}

void test_addListener(void) {
  // Create some EventListeners and an EventQueue
  mfsm_EventListener el1;
  mfsm_EventListener el2;
  initEventListener(&el1);
  initEventListener(&el2);

  mfsm_EventQueue eq;
  initEventQueue(&eq);

  // Add the listeners to the EventQueue
  addListener(&eq, &el1);
  addListener(&eq, &el2);

  // Test if the listeners were added to the EventQueue.
  if (eq.listeners[0] != &el1) {
    printf("EventListener #1 was not successfully added\n");
    printf("Expected: %p\n", &el1);
    printf("Found:    %p\n", eq.listeners[0]);
  }
  assertMsg(eq.numListeners == 1, "numListeners was not updated");

  if (eq.listeners[1] != &el2) {
    printf("EventListener #2 was not successfully added\n");
    printf("Expected: %p\n", &el2);
    printf("Found:    %p\n", eq.listeners[1]);
  }
  assertMsg(eq.numListeners == 2, "numListeners was not updated");

  report("addListener()");
}

void test_removeListener(void) {
  // Create some EventListeners and an EventQueue
  mfsm_EventListener el1;
  mfsm_EventListener el2;
  initEventListener(&el1);
  initEventListener(&el2);

  mfsm_EventQueue eq;
  initEventQueue(&eq);

  // Add the listeners to the EventQueue
  addListener(&eq, &el1);
  addListener(&eq, &el2);

  // Test if the listeners were added to the EventQueue.
  if (eq.listeners[0] != &el1) {
    printf("EventListener #1 was not successfully added\n");
    printf("Expected: %p\n", &el1);
    printf("Found:    %p\n", eq.listeners[0]);
  }
  assertMsg(eq.numListeners == 1, "numListeners was not updated");

  if (eq.listeners[1] != &el2) {
    printf("EventListener #2 was not successfully added\n");
    printf("Expected: %p\n", &el2);
    printf("Found:    %p\n", eq.listeners[1]);
  }
  assertMsg(eq.numListeners == 2, "numListeners was not updated");

  // Try to remove the listeners
  int i = removeListener(&eq, &el1);
  if (eq.listeners[0] != 0) {
    printf("EventListener #1 was not successfully removed\n");
    printf("Value: %p\n", eq.listeners[0]);
    printf("Error: %d\n", i);
  }
  assertMsg(eq.numListeners == 1, "numListeners was not updated");

  i = removeListener(&eq, &el2);
  if (eq.listeners[1] != 0) {
    printf("EventListener #2 was not successfully removed\n");
    printf("Value: %p\n", eq.listeners[1]);
    printf("Error: %d\n", i);
  }
  assertMsg(eq.numListeners == 0, "numListeners was not updated");

  report("removeListener()");
}


int main(int argc, char **argv) {
  printf("Running tests...\n\n");

  /****************************************
  * Test FSM System
  ****************************************/
  
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

  /****************************************
  * Test Event System
  ****************************************/

  // Event functions
  test_initEvent();
  test_appendEvent();
  test_getNextEvent();
  test_initEventQueue();
  test_addListener();
  test_removeListener();

  return 0;
}
