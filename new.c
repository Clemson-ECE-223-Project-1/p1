#include <stdio.h>
#include <stdlib.h>

typedef struct queue_s queue_t;

typedef struct event_s {
   int event_type;
   queue_t *queue;
   double event_time;
   //passenger_t *passenger;
} event_t;

typedef struct priority_s {
    int current_size;
    int max_size;
    event_t **event_tree;
} priority_t;

event_t *event_init(int time) {
   event_t *ev = (event_t *)malloc(sizeof(event_t));
   ev->event_type = -1;
   ev->queue = NULL;
   ev->event_time = time;

   if(ev == NULL) {
      printf("Cannot Intialize Event\n");
      return NULL;
   }

   return ev;
}

priority_t *priority_init(int size) {
    if(size < 0) {
        printf("Size < 0\n");
        return NULL;
    }
    
    priority_t *q = (priority_t *)malloc(sizeof(priority_t));
    q->max_size = size; // maximum size of tree
    q->current_size = 0;   // number of nodes in tree
    q->event_tree = (event_t **)malloc(size*sizeof(event_t)); // tree
    
    for(int i = 0; i < size; i++) {
        q->event_tree[i] = NULL;
    }

    if(q == NULL) {
        printf("Cannot Intialize Priority Queue\n");
        return NULL;
    }

    return q;
}

int priority_empty(priority_t *q) {
    int isEmpty = -1;

    if(q->current_size == 0) {
        isEmpty = 1;
        printf("Queue Empty\n");
    } else {
        isEmpty = 0;
    }

    return isEmpty;
}

int priority_full(priority_t *q) {
    int isFull = 0;

    if(q->current_size == q->max_size) {
        isFull = 1;
        printf("Queue Full\n");
    }

    return isFull;
}

void swap(double *a, double *b ) {
  double t;
  t = *a;
  *a = *b;
  *b = t;
}

int get_right_child(priority_t *q, int index) {
  if((((2*index)+1) < q->max_size) && (index >= 1))
    return (2*index)+1;
  return -1;
}

int get_left_child(priority_t *q, int index) {
    if(((2*index) < q->max_size) && (index >= 1))
        return 2*index;
    return -1;
}

int get_parent(priority_t *q, int index) {
  if ((index > 1) && (index < q->max_size)) {
    return index/2;
  }
  return -1;
}

//Function to make the array into a heap
static void heapify(priority_t *q, event_t *ev)
{//increasing the size of the array by 1 since the first element in the array needs to be empty
    q->current_size++;
    int child_pos, parent_pos;
    child_pos = q->current_size;
    parent_pos = child_pos/2;

    //if the parent position is the zero'th element, then skip this loop since it should be empty
    while(parent_pos != 0)
    {//if the event time is greater than the parent's event time, make this the chid's value since this is an
     //array that should have small values higher in the heap as opposed to large values
        if(ev->event_time >= q->event_tree[parent_pos]->event_time)
        {//set the child's priority value
            q->event_tree[child_pos] = ev;
            return;
        }
        else
        {//if the function makes it to this part, that means the parent is larger than the child (which shouldn't be the case)
         //sets the child as the old's parents position and moves the parent's position up a level
            q->event_tree[child_pos] = q->event_tree[parent_pos];
            child_pos = parent_pos;
            parent_pos = parent_pos/2;
        }
    }//set the child's priority value
    q->event_tree[child_pos] = ev;
}

int priority_insert(priority_t *q, event_t *ev) {
    int full, empty, success;

    full = priority_full(q);
    empty = priority_empty(q);
    success = 1;

    if(full == 1) {
        success = -1;
    } else if(empty == 1) {
        q->current_size++;
        q->event_tree[1] = ev;
        success = 0;
    } else {
        heapify(q, ev);
        success = 0;
    }

    return success;
}

static void reheapify(priority_t *q) {
    int current_pos = 1;
    int child_pos = 2*current_pos;
    event_t *ev;
    ev = q->event_tree[q->current_size];
    q->event_tree[q->current_size] = NULL;
    q->current_size--;

    if(priority_empty(q) != 1) {
        while(child_pos <= q->current_size) {
            if(child_pos < q->current_size) {
                double right_child = q->event_tree[child_pos+1]->event_time;
                double left_child = q->event_tree[child_pos]->event_time;

                if(right_child < left_child)
                    child_pos++;
            }

            if(q->event_tree[child_pos]->event_time >= ev->event_time)
                break;
            else {
                q->event_tree[current_pos] = q->event_tree[child_pos];
                current_pos = child_pos;
                child_pos = 2*child_pos;
            }
            
        }
        q->event_tree[current_pos] = ev;
    }
}

//remove the root (highest priority) of the heap
event_t *priority_remove(priority_t *q)
{
    int empty = priority_empty(q);
    event_t *removal;
    
    if(empty == 1) {
        removal = NULL;
    } else {
        removal = q->event_tree[1];
        q->event_tree[1] = q->event_tree[q->current_size];
        reheapify(q);
    }

    return removal;
}

void print_heap(priority_t *q) {
  for(int i = 1; i <= q->current_size; i++) {
    printf("%f\n", q->event_tree[i]->event_time);
  }
  printf("\n");
}

int main() {

  priority_t *q = priority_init(10);

  event_t *event = event_init(12);
  int one_twelve = priority_insert(q, event);
  printf("one = %d\n", one_twelve);
  printf("size: %d\n\n", q->current_size);
  printf("Heap: \n");
  print_heap(q);

  event_t *event2 = event_init(3);
  int two_three = priority_insert(q, event2);
  printf("two = %d\n", two_three);
  printf("size: %d\n", q->current_size);
  printf("Heap: \n");
  print_heap(q);

  event_t *event3 = event_init(20);
  int three_twenty = priority_insert(q, event3);
  printf("three = %d\n", three_twenty);
  printf("size: %d\n", q->current_size);
  printf("Heap: \n");
  print_heap(q);

  event_t *event4 = event_init(5);
  int four_five = priority_insert(q, event4);
  printf("four = %d\n", four_five);
  printf("size: %d\n", q->current_size);
  printf("Heap: \n");
  print_heap(q);

  event_t *event5 = event_init(1);
  int five_one = priority_insert(q, event5);
  printf("five = %d\n", five_one);
  printf("size: %d\n", q->current_size);
  printf("Heap: \n");
  print_heap(q);

  event_t *event6 = event_init(6);
  int six_six = priority_insert(q, event6);
  printf("six = %d\n", six_six);
  printf("size: %d\n", q->current_size);
  printf("Heap: \n");
  print_heap(q);

  event_t *event7 = priority_remove(q);
  printf("Remove Root %f\n", event7->event_time);
  printf("size: %d\n", q->current_size);
  printf("Heap: \n");
  print_heap(q);

  event_t *event8 = priority_remove(q);
  printf("Remove Root %f\n", event8->event_time);
  printf("size: %d\n", q->current_size);
  printf("Heap: \n");
  print_heap(q);

  event_t *event9 = priority_remove(q);
  printf("Remove Root %f\n", event9->event_time);
  printf("size: %d\n", q->current_size);
  printf("Heap: \n");
  print_heap(q);

  return 0;
}
