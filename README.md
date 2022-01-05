# 42Minishell

The objective of this project is for you to create a simple shell.

## Prerequisites

This project is for Mac OS.

## Installation

* `git clone git@github.com:MLeganes/42Minishell.git` this repository
* `cd 42Minishell`

## Running
 
* `make`

* Run program with ``` ./minishell```
  

## Useful Links

* [WritingYourOwnShell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
* [mysh](https://github.com/Swoorup/mysh)
* [shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)


## Sanitize

Add -g in gcc command.

	-fsanitize=leak
	-fsanitize=address


## Print traces

Add in header file this define:

	# define PRINT_HERE() (printf("file: %s, line: %d\n", __FILE__, __LINE__))

And used it from any part of your program

	PRINT_HERE();