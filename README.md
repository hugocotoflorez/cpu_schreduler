# cpu schreduler

### Quick resume

This schreduler use tickets to give
processes 'relevance'. Once a process run
in the cpu for a time slice (max time that a process
run without os decisions) the stride (ticket value * times proc runs)
increments by ticket value. The next process that is going to run
in the cpu is the active process with the lowest stride.

### Handle I/O

Processes can enter in io mode, in a random way
(only the process that is running in the cpu),
as well as exit io mode.

### Data structures

 - `Active processes`: Stored in a sorted list,
 it should be a black-red tree (as some linux book said).
 - `Inactive processes`: Stored into a dynamic array aka stack.

[!ATTENTION]
> I do this some random morning, dont expect pretty output or elavorated stuff
