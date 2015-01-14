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
* from the Listener's first-in-first-out stack.
*
* This is something of an Observer pattern with polling instead of function
* pointers. This way each listening object gets its own stack of events to
* process independently. This system will probably be redesigned at some point.
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
