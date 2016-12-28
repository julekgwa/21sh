# 21sh
mini UNIX command interpreter.

21sh uses my own implementation of libc's functions, most of them start with `ft_`

21sh implements:

* A series of builtins
 * echo 
 * cd
 * setenv
 * unsetenv
 * env
 * exit
* History
 * history n
 * history -c
 * !string
 * !n
 * !! and !-1
 * CTRL+R (reverse-i-search)
 * :arrow_up: UP or :arrow_down: DOWN
* Copy and Paste
 * CTRL-W - Copy what is currently in front of the cursor.
 * CTRL-I - Copy the entire line that has being typed.
 * CTRL-K - Cut or delete what is currently in front of the cursor.
 * CTRL-X - Cut or delete the entire line that has being typed.
 * CTRL-V - Paste the last thing you deleted (using CTRL-K, CTRL-W, CTRL-I or CTRL-X ).
* Auto complete
* unset
* export
* line edition
* the “;” command line separator
* pipes “|”
* redirections “<”, “>”, “<<” & “>>”
* file descriptor aggregation (e.g. ``2>&-`` & ``1>&2``)
* Go directly to the beginning or the end of a line by pressing home and end.
* Move directly by word towards the left or the right using ctrl+LEFT and ctrl+RIGHT.

# Installation
```
$ git clone https://github.com/julekgwa/21sh.git
```

# Usage
```
$ cd 21sh
$ make && ./21sh

```
# License
MIT