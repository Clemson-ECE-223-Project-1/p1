#include <stdlib.h>
#include <stdio.h>
#include "priority.h"
#include "event.h"


//initialize the priority heap-array
priority_t *priority_init(int size)
{
    if (size < 0)
        return NULL;

     priority_t *p = (priority_t *)malloc(sizeof(priority_t));
     p->max_size = size;
     p->current_size = 0;
     p->event_tree = (event_t *)malloc(size*sizeof(event_t));

     for (int i = 0; i < size; i++)
        p->event_tree[i] = NULL;

    if(p == NULL)
        return NULL;

    return p;
}

//Function to make the array into a heap
static void heapify(priority_t *q, event_t *ev)
{
    q->current_size = q->current_size++;
    int child_pos, parent_pos;
    child_pos = q->current_size;
    parent_pos = child_pos/2;

    while(parent_pos != 0)
    {
        if(ev->event_time >= q->event_tree[parent_pos]->event_time)
        {
            q->event_tree[child_pos] = ev;
            return;
        }
        else
        {
            q->event_tree[child_pos] = q->event_tree[parent_pos];
            child_pos = parent_pos;
            parent_pos = parent_pos/2;
        }
    }
    q->event_tree[child_pos] = ev;
}

static void reheapify(priority_t *q)
{
    int current_pos = 1;
    int child_pos = 2*current_pos;
    event_t ev;
    ev = q->event_tree[eq->tree_size];
    q->event_tree[q->tree_size] = NULL;
    q->tree_size--;

    if(priority_empty(q) != 1)
    {
        while(child_pos <= q->tree_size)
        {
            if(child_pos < q->tree_size)
            {
                double right_child = q->event_tree[child_pos+1]->event_time;
                double left_child = q->event_tree[child_pos]->event_time;

                if(right_child < left_child)
                    child_pos = child_pos++;
            }

            if(q->event_tree[child_pos]->event_time >= ev->event_time)
                break;
            else
            {
                q->event_tree[current_pos] = q->event_tree[child_pos];
                current_pos = child_pos;
                child_pos = 2*child_pos;
            }
            
        }
        q->event_tree[current_pos] = ev;
    }
}

//insert an event into the priority heap-array.
//0 for success, -1 otherwise
int priority_insert(priority_t *q, event_t *ev)
{
    int full;
    int empty;
    int success;

    full = priority_full(q);
    empty = priority_empty(q);

    if(full == 1)
        success = -1;
    else if(empty == 1)
    {
        q->current_size = q->current_size++;
        q->event_tree[1] = ev;
        success = 0;
    }
    else
    {
        heapify(q, ev);
        success = 0;
    }
    
}

//remove the root (highest priority) of the heap
event_t *priority_remove(priority_t *q)
{
    int empty;
    empty = priority_empty(q);
    event_t removal;
    
    if(empty == 1)
        removal = NULL;
    else
    {
        removal = q->event_tree[1];
        reheapify(q);
    }

    return removal;
}

//check to see if the heap is empty
//1 if empty, 0 otherwise
int priority_empty(priority_t *q)
{
    int empty;

    if (q->count == 0)
        empty = 1;
    else
        empty = 0;

    return empty;
}

//check to see if the heap is full
//1 if full, 0 otherwise
int priority_full(priority_t *q)
{
    int full;

    if(q->count == q->size)
        full = 1;
    else
        full = 0;
    
    return full;
}

//free pointers used by the heap, and then free the heap
void priority_finalize(priority_t *q)
{
    for(int i = 0; i < q->current_size; i++)
    {
        free(q->event_tree[i]);
        q->event_tree[i] = NULL;
    }
    
    free(q->event_tree);
    q->event_tree = NULL;

    free(q);
    q = NULL;
}
