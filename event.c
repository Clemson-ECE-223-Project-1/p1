/* event.c */

#include "event.h"
#include <stdio.h>
#include <stdlin.h>

/* initializes events, creates a priority queue */
void event_init() {
   event_t *ev = (event_t *)malloc(sizeof(event_t));
   ev->event_type = -1;
   ev->queue = NULL;
   ev->event_time = -1;
   ev->passgener = NULL;

   if(ev == NULL) {
      printf("Cannot Intialize Event\n");
      return NULL;
   }
}

/* frees up all event space, including space in the priority queue */
void event_fini() {

}

/* allocate a fresh event with empty fields */
event_t *event_create() {

}

/* free an event */
void event_destroy(event_t *e) {

}

/* insert the event into the priority queue.  The key
   value is the current sim time plus the event_time in
   event.  Update the event time to the key value. */
void event_schedule(event_t *e) {

}

/* remove the next event from the priority and return it to the program for execution */
event_t *event_cause() {

}

double event_time(event_t ev) {
   
   return ev->time;
}
