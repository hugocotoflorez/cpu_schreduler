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

