#include "shareobjs.h"
#include <stdlib.h> // malloc

void pseudotree_insert(Pseudotree* t, Proc p)
{
    struct node *new_node = malloc(sizeof(struct node)), *current;
    new_node->proc        = p;
    new_node->next        = NULL;

    if (t->first == NULL || t->first->proc.currency > new_node->proc.currency)
    {
        new_node->next = t->first;
        t->first       = new_node;
        return;
    }

    current = t->first;
    while (current->next != NULL &&
    current->next->proc.currency <= new_node->proc.currency)
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next  = new_node;
}

Proc pseudotree_remove_head(Pseudotree* t)
{
    struct node* temp_n;
    Proc temp_p;

    if (t->first == NULL)
        return (Proc){ 0 };

    temp_n   = t->first;
    temp_p   = t->first->proc;
    t->first = t->first->next;

    free(temp_n);
    return temp_p;
}

Proc pseudotree_get_head(Pseudotree* t)
{
    if (t->first == NULL)
        return (Proc){ 0 };

    return t->first->proc;
}

#include <stdio.h>
void pseudotree_print(Pseudotree* t)
{
    for (struct node* curr = t->first; curr != NULL; curr = curr->next)
    {
        printf("Proc %c (pid: %-4d) stride: %2.d, currency: %4.d\n",
        curr->proc.pid, curr->proc.pid, curr->proc.stride, curr->proc.currency);
    }
}
