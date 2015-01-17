#ifndef EVENT_H
#define EVENT_H

#define MAX_EVENT_LISTENERS 32
#define MAX_EVENTS 32

/*****************************************************************************
* MFSM Event System
*
* Handles Input and Output events for FSM transitions. An EventQueue
* dispatches Event structures to registered EventListener structures. Use the
* addListener() function to register an EventListener. The user must poll the
* numEvents integer in the EventListener to watch for incoming events stored
* in the same structure. Use the getNextEvent() function to retrieve Events
* from the Listener's first-in-first-out queue.
*
* This is something of an Observer pattern with polling instead of function
* pointers. This way each listening object gets its own queue of events to
* process independently. This system will probably be redesigned at some
* point.
*****************************************************************************/


/*****************************************************************************
* struct Event
*
* Stores data for input/output events sent from Finite State Machine
* transitions.
*
* TODO: Add a type variable and the ability to receive only events of specific
* types.
*****************************************************************************/
typedef struct mfsm_Event{
  // Unique identifier for the event. Preferably used with an enumerated type
  // made by the user.
  int id; 
} mfsm_Event;

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
void initEvent(mfsm_Event *e, int id);

/*****************************************************************************
* struct EventListener
*
* Stores Events for processing at the receiver's convenience. Poll numEvents
* for changes, then use getNextEvent() to retrieve them one at a time.
*****************************************************************************/
typedef struct mfsm_EventListener{
  mfsm_Event events[MAX_EVENTS]; // Events waiting for processing
  int numEvents;                 // Number of Events in the events array
} mfsm_EventListener;


// void initEventListener(mfsm_EventListener*)
//
// Set default values for an EventListener.
//
// Parameters:
// el    mfsm_EventListener*   Uninitialized EventListener struct
//
// Returns:
// None
void initEventListener(mfsm_EventListener *el);

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
// Success: New number of events in the stack
// Failure:
//  -1 -- Null/invalid EventListener
//  -2 -- Null/invalid destination
//  -3 -- No events to be retrieved from the EventListener
int getNextEvent(mfsm_EventListener *el, mfsm_Event* dest);

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
int appendEvent(mfsm_EventListener *el, mfsm_Event e);

/*****************************************************************************
* struct EventQueue
*
* Stores EventListeners for sending events.
*****************************************************************************/
typedef struct mfsm_EventQueue{
  // Registered listeners to send Events to
  mfsm_EventListener *listeners[MAX_EVENT_LISTENERS];
  int numListeners; // Number of EventListeners currently registered
} mfsm_EventQueue;

#endif //EVENT_H
