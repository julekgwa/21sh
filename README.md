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
* line edition
* the “;” command line separator
* pipes “|”
* redirections “<”, “>”, “<<” & “>>”
* file descriptor aggregation

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