Storage Limit
-------------

The maximum storage limit can be set using the command

    config storage_limit number

where, `number` is an integer.

Each state for size 9 Sudoku has roughly (81+1)*2*sizeof(int) = 656 bytes
of storage.  A 1.5 Gbyte storage limit would suggest (1.5)*(10^9) / 656
which is approximately 2100000 states.


