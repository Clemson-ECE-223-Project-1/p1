#include <stdlib.h>
#include <stdio.h>
#include "priority.h"

/*struct priority_s
{
    int count;
    int priority;
    int myarray;

}priority_t;
*/
priority_t *priority_init(int size)
{
    if (size < 0)
        return NULL;

    //int array[size] = {0};
    //array = malloc(sizeof(int)*size+1);
   // priority_t *p = (priority_t *)malloc(sizeof(priority_t) + a*sizeof(int));
     priority_t *p = (priority_t *)malloc(sizeof(priority_t));
     p->myarray = (int*)malloc(sizeof(int) * size);


    //p = myarray[size+1] = {0};    
    p->count = 0;
    p->priority = 0;

    if(p == NULL)
        return NULL;

    return p;
}

int priority_insert(priority_t *q, event_t *ev)
{

}

event_t *priority_remove(priority_t *q)
{

}

int priority_empty(priority_t *q)
{
    int empty;

    if (q->count == 0)
        empty = 1;
    else
        empty = 0;

    return empty;
    
}

int priority_full(priority_t *q)
{

}

void priority_finalize(priority_t *q)
{
    //there may need to be a line of code here but will revise later
    q = NULL;
    free(q);
}
