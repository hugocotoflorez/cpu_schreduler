#include "shareobjs.h"
#include <stdlib.h>
#include <unistd.h>
// Just printf
#include <stdio.h>

/*
 * Author: Hugo Coto Florez
 * Source: OSTEP 2023 printed edition
 */

#define VERBOSE 3     // Full verbose
#define TIME_SLICE 20 // ms

int curr_pid = 'A';
#define random_proc                                                               \
    (Proc)                                                                        \
    {                                                                             \
        .active = 1, .pid = curr_pid++, .stride = rand() % 15,                    \
        .priv.runtime_ms_left = rand() % 500, .priv.io = (float)(rand() % 5) / 10 \
    }

void schredule(Proc* p)
{
    if (VERBOSE > 1)
        printf("Executing proc (pid: %-3d) (%.3d ms left)", p->pid, p->priv.runtime_ms_left);
    p->currency += p->stride;
    p->priv.runtime_ms_left -= TIME_SLICE;
    p->active = rand() % 10 >= p->priv.io * 10; // set if on io
    // if proc on io or end before slice, return
}

int main(int argc, char* argv[])
{
    Stack inactive_procs    = { 0 };
    Pseudotree active_procs = { 0 };
    Proc current, temp;
    char* exec_timeline = NULL;
    int timeline_len    = 0;

    pseudotree_insert(&active_procs, random_proc);
    pseudotree_insert(&active_procs, random_proc);
    pseudotree_insert(&active_procs, random_proc);

    pseudotree_print(&active_procs);
    putchar('\n');

    do
    {
        current = pseudotree_remove_head(
        &active_procs); // current is the active proc with the lowest currency


        schredule(&current); // execute current proc on the cpu


        if (current.priv.runtime_ms_left <= 0)
        {
            if (VERBOSE > 1)
                puts("[terminate]"); // proc terminate
        }
        else if (current.active == 1)
        {
            if (VERBOSE > 1)
                puts("[ok]");
            pseudotree_insert(&active_procs, current); // if still active insert into the tree
        }
        else
        {
            if (VERBOSE > 1)
                puts("[on io]");
            stack_insert(&inactive_procs, current); // if on io insert into the stack
        }

        exec_timeline = realloc(exec_timeline, ++timeline_len);
        exec_timeline[timeline_len - 1] = current.pid;


        awake_some_io_proc(&inactive_procs); // simulate end of io requests

        // move active processes from the stack to the tree
        while ((temp = stack_remove_active(&inactive_procs)).pid > 0)
        {
            temp.currency = pseudotree_get_head(&active_procs).currency;
            pseudotree_insert(&active_procs, temp);
        }


        if (VERBOSE > 1)
            sleep(1); // just to read output

        if (VERBOSE > 2)
        {
            putchar('\n');
            stack_print(&inactive_procs);
            pseudotree_print(&active_procs);
            putchar('\n');
        }

    } while (current.pid != 0 || inactive_procs.ptr > 0); // stop when no processes remaining


    puts("timeline");
    for (int i = 0; i < timeline_len; i++)
    {
        printf("%c ", exec_timeline[i]);
    }

    return 0;
}
