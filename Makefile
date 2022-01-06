# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 11:49:03 by amorcill          #+#    #+#              #
#    Updated: 2022/01/06 13:59:27 by amorcill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= clang
#FLAGS	= -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=address
FLAGS	= -Wall -Wextra -Werror -g
OBJS	= $(patsubst %.c, %.o, $(SRCS))
SRCS	=	minishell.c \
 
%.o: %.c
	$(CC) $(FLAGS) -Ilibft -c $< -o $@

all: $(NAME)

$(NAME): libft/libft.a $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -Llibft -lreadline -lft -o $(NAME) 

clean:
	rm -f *.o
	rm -f *.out
	make -C libft clean

fclean: clean
	make -C libft fclean	
	rm -f $(NAME)

re: fclean $(NAME)
	
libft/libft.a:
	make -C libft all
