/* event.c */

#include "priority.h"
#include "time.h"

#include <stdio.h>
#include <stdlib.h>

static priority_t *q = NULL;

/* initializes events, creates a priority queue */
void event_init() {
    if(q == NULL)
    {
        q = priority_init(3);
        if(q == NULL)
        {
            printf("Cannot Intialize Event\n");
        }
    }

}

/* frees up all event space, including space in the priority queue */
void event_fini() {
    priority_finalize(q);
}

/* allocate a fresh event with empty fields */
event_t *event_create() {
    event_t *ev = (event_t *)malloc(sizeof(event_t));
    ev->passenger = (passenger_t *)malloc(sizeof(passenger_t));

    if(ev == NULL || ev->passenger == NULL)
    {
        printf("Issue with your event/event passenger data.");
        return NULL;
    }
    return ev;
}

/* free an event */
void event_destroy(event_t *e) {
    free(e->passenger);
    free(e);
}

/* insert the event into the priority queue.  The key
   value is the current sim time plus the event_time in
   event.  Update the event time to the key value. */
void event_schedule(event_t *e) {
    double key_time = time_get();
    key_time += e->event_time;
    priority_insert(q, e);
}

/* remove the next event from the priority and return it to the program for execution */
event_t *event_cause() {
    event_t *event = priority_remove(q);
    if(event == NULL)
    {
        printf("The queue is empty.");
        return NULL;
    }
    return event;
}

double event_time(event_t *e) {
   return e->event_time;
}
