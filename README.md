# RSHELL

This project is to write a command shell called `rshell`. This shell prints the command prompt `$`. The shell allows for multiple commands to be passed  into the command line. The commands cann be separated by `;` or they can be connected by `&&`,`||`,and also by `&`,`|`. The commands are executed from left to right. If the commands are chained together with `and` symbol then the following command will only execute if the first one succeded in executign.  If the commands are cahined by `or` symbols then the next command will only execute if the   first one failed. 
The following command should run without problems:
`ls -a; echo hello && mkdir test || echo world; cd test`



##know bugs

The `rshell` had a couple of memory leak bugs but they should have been fixed by `free()` and `delete[]`.
Before adding the `free()` command i had the error:
`Aborted(core dumped)`
This message has not showed up since the last few commits after fixing the memory leaks.
 
