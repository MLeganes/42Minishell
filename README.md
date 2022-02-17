# 42Minishell

The objective of this project is for you to create a simple shell.

## Prerequisites

This project is for Mac OS.

For Linux distribution, need to install the readline development libraries.

	sudo apt-get install libreadline-dev 
	

## Installation

* `git clone git@github.com:MLeganes/42Minishell.git` this repository
* `cd 42Minishell`

## Running
 
* `make`

* Run program with ``` ./minishell```
  
## Shell Operation
![shell_operation](readme_additions/shell_operation.png)

## Useful Links

* [WritingYourOwnShell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
* [mysh](https://github.com/Swoorup/mysh)
* [shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
* [GNU-manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/)


# Commands

## echo

	"ec"ho" str"ing"					cmd: NOt found.
	e"cho hello"						cmd: bash: echo hello: command not found
	echo "hello " | cat -e ech"o" "he"llo"o"				cmd: cat: echo: No such file or directory

## Tester
	cd /tests
	bash tester.sh -f cmds/mand/0_mand.sh

	you can also add new tests


## Sanitize

Add -g in gcc command.

	-fsanitize=leak
	-fsanitize=address


## Print traces

Add in header file this define:

	# define PRINT_HERE() (printf("file: %s, line: %d\n", __FILE__, __LINE__))

And used it from any part of your program

	PRINT_HERE();


# Dockers and Valgrind

 [42toolbox](https://github.com/alexandregv/42toolbox)
 [guide](https://www.gungorbudak.com/blog/2018/06/13/memory-leak-testing-with-valgrind-on-macos-using-docker-containers/)

## Dockerfile

	FROM ubuntu:16.04
	RUN apt-get update
	RUN apt-get upgrade -y
	RUN apt-get install g++ valgrind -y
	RUN apt-get install libreadline6 libreadline6-dev
	RUN apt-get update && apt-get install make

## Build docker

	docker build -t memory-test:0.1 .

## Run docker in project folder

	docker run -ti -v $(PWD):/test memory-test:0.1 bash -c "cd /test/; make && valgrind --leak-check=full --show-leak-kinds=all ./minishell; rm -f ./minishell"

# Brew

Installing:

	rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update

Notes:
Failure while executing; `/Users/amorcill/.brew/bin/brew tap homebrew/core` exited with 1.
==> Tapping homebrew/core
Cloning into '/Users/amorcill/.brew/Library/Taps/homebrew/homebrew-core'...

# Readline lib.

Installing:

	brew install readline

For compilers to find readline you may need to set:
	export LDFLAGS="-L$(HOME).brew/opt/readline/lib"
	export CPPFLAGS="-I$(HOME).brew/opt/readline/include"


	READLINE = 	-L$$HOME/.brew/opt/readline/lib -lreadline \
				-I$$HOME/.brew/opt/readline/include \


# Checklist
[ ] To be done. [X] Done. 

- [ ] echo $? # after command not found is WRONG. It should be 127.
- [ ] echo $? # After this command: '/bin/ls filethatdoesntexis' it should be 2.

- [ ] export: Export environment variables, create new ones, and replace old ones 				NO WORKING

- [ ] exit with +num or -num
- [ ] how to check if $PATH is checked from left to right (dir1:dir2)
- [ ] redir: if file does not exist we create it (we should not create the file)
- [X] unset does not work anymore
- [X] cat | ls (Ang) << I work today on this!
- [X] << end cat > file 
