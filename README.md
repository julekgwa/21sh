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
* Copy and Paste
 * CTRL-K - Cut or delete what is currently in front of the cursor.
 * CTRL-X - Cut or delete the entire line that has being typed.
 * CTRL-P - Paste the last thing you deleted (using CTRL-K or CTRL-X ).
* line edition
* the “;” command line separator
* pipes “|”
* redirections “<”, “>”, “<<” & “>>”
* file descriptor aggregation (e.g. ``2>&-`` & ``1>&2``)

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