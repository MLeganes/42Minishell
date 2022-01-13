# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 11:49:03 by amorcill          #+#    #+#              #
#    Updated: 2022/01/13 11:53:45 by amorcill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= clang
FLAGS	= -Wall -Wextra -Werror -g
OBJS	= $(patsubst %.c, %.o, $(SRCS))
SRCS	=	minishell.c lexer.c free.c \
 
%.o: %.c
	$(CC) $(FLAGS) -Ilibft -c $< -o $@

all: $(NAME)

$(NAME): libft/libft.a $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -Llibft -lreadline -lft -o $(NAME) 
	@echo "\033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"
clean:
	@rm -f *.o
	@rm -f *.out
	@make -C libft clean
	@echo "\033[31mObjects Files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31mremoved.\033[0m"

fclean: clean
	@make -C libft fclean	
	@rm -f $(NAME)
	@echo "\033[1;31m$(NAME)\033[1;0m\033[31m Removed.\033[0m"

re: fclean $(NAME)
	
libft/libft.a:
	make -C libft all
