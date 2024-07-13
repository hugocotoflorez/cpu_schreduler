#ifndef _LIB_H
#define _LIB_H

typedef int pid_t;
typedef struct proc Proc;
typedef struct stack Stack;
typedef struct pseudotree Pseudotree;

struct proc
{
    pid_t pid, // proceess id
    currency,  // measurement of priority level
    stride,
    active; // bool: process can run now
    struct
    {
        int runtime_ms_left; // time that the proc is going to run
        float io;            // from 0 to 1, probability of io task
    } priv;
};

struct stack
{
    int size, // size
    ptr;      // last element index +1
    Proc* items;
};

void stack_insert(Stack*, Proc);
Proc stack_remove_active(Stack*);
void awake_some_io_proc(Stack*);
void stack_print(Stack* s);
void stack_destroy(Stack* s);

/*
 * This should be a tree
 * but is a sorted list
 * first element is the smaller stride
 */

struct node
{
    Proc proc;
    struct node* next;
};

struct pseudotree
{
    struct node* first;
};

void pseudotree_insert(Pseudotree* t, Proc p);
Proc pseudotree_remove_head(Pseudotree* t);
Proc pseudotree_get_head(Pseudotree* t);
void pseudotree_print(Pseudotree* t);
void pseudotree_destroy(Pseudotree* t);

#endif // _LIB_H
