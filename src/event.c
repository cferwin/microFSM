#include "event.h"

/*****************************************************************************
* Event functions
*****************************************************************************/

// void initEvent(mfsm_Event*, int)
//
// Set default values for an Event.
//
// Parameters:
// e    mfsm_Event*   Uninitialized Event struct
// id   int           Unique identifier for the event
//
// Returns:
// None
void initEvent(mfsm_Event *e, int id) {
  e->id = id;
}

/*****************************************************************************
* EventListener functions
*****************************************************************************/

// void initEventListener(mfsm_EventListener*)
//
// Set default values for an EventListener.
//
// Parameters:
// el    mfsm_EventListener*   Uninitialized EventListener struct
//
// Returns:
// None
void initEventListener(mfsm_EventListener *el) {
  el->numEvents = 0;
}

// int getNextEvent(mfsm_EventListener*, mfsm_Event*)
//
// Dequeue operation. Removes the oldest Event from the EventListener and
// copies it to a specified destination.
//
// Parameters:
// el     mfsm_EventListener*   EventListener context
// dest   mfsm_Event*           Destination to copy the event data to
//
// Returns:
// Success: New number of events in the queue
// Failure:
//  -1 -- 0/invalid EventListener
//  -2 -- 0/invalid destination
//  -3 -- No events to be retrieved from the EventListener
int getNextEvent(mfsm_EventListener *el, mfsm_Event* dest) {
  // Validate as much as possible before trying to copy data
  if (el == 0) {
    return -1;
  }

  if (dest == 0) {
    return -2;
  }

  if (el->numEvents < 1) {
    return -3;
  }

  // Copy the data from the most recent event to the destination
  // TODO: This works for now, but make it more readable when more variables
  // are added to the mfsm_Event structure.
  dest->id = el->events[el->numEvents-1].id;

  el->numEvents--; // Controlling the event array makes destroying the Event
                   // unnecessary.

  return el->numEvents;
}

// int appendEvent(mfsm_EventListener*, Event)
//
// Enqueue operation. Adds an Event to the end of the EventListener's queue.
//
// Parameters:
// el   mfsm_EventListener*   EventListener context
// e    mfsm_Event            Event to be stored
//
// Returns:
// Success -- New number of events in the queue
// Failure:
//  -1 -- Invalid EventListener
//  -2 -- No more room in the EventListener
int appendEvent(mfsm_EventListener *el, mfsm_Event e) {
  // Validate as much as possible before trying to copy data
  if (el == 0) {
    return -1;
  }

  if (el->numEvents >= MAX_EVENTS) {
    return -2;
  }

  // Copy the data from the most recent event to the destination
  // TODO: This works for now, but make it more readable when more variables
  // are added to the mfsm_Event structure.
  el->events[el->numEvents-1].id = e.id;

  el->numEvents++;

  return el->numEvents;
}

/*****************************************************************************
* EventQueue functions
*****************************************************************************/

// void initEventQueue(mfsm_EventQueue*)
//
// Set default values for an EventQueue.
//
// Parameters:
// eq    mfsm_EventQueue*   Uninitialized EventQueue struct
//
// Returns:
// None
void initEventQueue(mfsm_EventQueue *eq) {
  eq->numListeners = 0;
}
