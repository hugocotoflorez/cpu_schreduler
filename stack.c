#include "shareobjs.h"
#include <stdlib.h> // realloc

#define ST_INC 1;         // increment as a sum
#define IO_AWAKE_PROB 0.2 // aprox 5 cycles

/*
 * stack_insert(s, p) -> [ Insert p into s ]
 * Add a new proc to the stack at it last (ptr-1) position, and update ptr.
 * If stack is full, realloc stack.
 */
void stack_insert(Stack* s, Proc p)
{
    if (s->size > s->ptr)
    {
        s->items[s->ptr] = p;
        ++s->ptr;
    }
    else
    {
        s->size          = s->size + ST_INC;
        s->items         = realloc(s->items, s->size * sizeof(Proc));
        s->items[s->ptr] = p;
        ++s->ptr;
    }
}

/*
 * stack_remove_active(s) -> [ -> active process | null-proc (pid=0) ]
 * Remove the fist active process into stack if exist, otherwise 0
 */
void __swap(Stack* s, int i, int j)
{
    Proc temp   = s->items[i];
    s->items[i] = s->items[j];
    s->items[j] = temp;
}

Proc stack_remove_active(Stack* s)
{
    for (int i = 0; i < s->ptr; i++)
    {
        if (s->items[i].active == 1)
        {
            --s->ptr;
            for (int k = i; k < s->ptr; k++)
                __swap(s, k, k + 1); // move the active proc to the last position

            return s->items[s->ptr]; // return the item at last position and update ptr
        }
    }
    return (Proc){ 0 };
}

void awake_some_io_proc(Stack* s)
{
    for (int i = 0; i < s->ptr; i++)
        if (s->items[i].active == 0)
            s->items[i].active = rand() % 100 <= IO_AWAKE_PROB * 100;
}

#include <stdio.h>
void stack_print(Stack* s)
{
    Proc curr;
    for (int i = 0; i < s->ptr; i++)
    {
        curr = s->items[i];
        printf("Proc %c (pid: %-4d) tickets: %2.d, stride: %4.d [on io]\n",
        curr.pid, curr.pid, curr.tickets, curr.stride);
    }
}
