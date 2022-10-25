# Gdb

###### Core file configuration

/proc/sys/kernel/core_pattern

###### gdb.txt

```
bt
bt full
info proc all
info registers
info shared
info signals
info target
info threads
thread apply all bt
quit
```

###### Analyze core with the gdb.txt

cat gdb.txt | gdb PROGRAM CORE >/tmp/gdb.out

###### Analyze core in alternative location

set solib-absolute-prefix .

exec-file PROGRAM

core CORE