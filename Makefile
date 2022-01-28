# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 11:49:03 by amorcill          #+#    #+#              #
#    Updated: 2022/01/28 16:38:47 by amorcill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror -g

S		=	src/
O		=	obj/
B		=	builtin/
E 		=	exec/
N 		=	environment/
P		=	parser/

OBJS	= 	$(patsubst $S%.c, $O%.o, $(SRCS))
SRCS	=	$Sminishell.c $Slexer.c \
			$S$Pparser.c $S$Pparser_redir.c  \
			$S$Bms_cd.c $S$Bms_pwd.c $S$Bms_echo.c $S$Bms_builtin.c \
			$S$Nenv.c $S$Nenv_get.c \
			$S$Eexecute.c $S$Eexecute_parent.c $S$Eexecute_child.c \
			$Ssignal.c  $Sfree.c \

INCRL		=-I$(HOME)/.brew/opt/readline/include
LIBRL		=-L$(HOME)/.brew/opt/readline/lib -lreadline

LIBRARIES	=-Llibft -lft $(LIBRL)
INCLUDES	=-I ./inc -Ilibft $(INCRL)

all:		$(NAME)
# Linking
$(NAME):	libft/libft.a $(OBJS)
			@echo "\033[1;32m$(NAME)\033[1;0m\033[32m linking..\033[0m"
			@$(CC) $(FLAGS) $(OBJS) $(LIBRARIES) -o $(NAME) 
			@echo "\033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

# Compiling
$O%.o:		$S%.c
			@[ -d $(O) ]	 || mkdir -p $(O)
			@[ -d $(O)$(B) ] || mkdir -p $(O)$(B)
			@[ -d $(O)$(N) ] || mkdir -p $(O)$(N)
			@[ -d $(O)$(E) ] || mkdir -p $(O)$(E)
			@[ -d $(O)$(P) ] || mkdir -p $(O)$(P)
			@echo "\033[1;32m$(NAME)\033[1;0m\033[32m compiling...\033[0m"
			@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
			@rm -rf $(O)
			@rm -rf $(NAME)
			@make -C libft clean
			@echo "\033[31mObjects Files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31mremoved.\033[0m"

fclean: 	clean
			@make -C libft fclean	
			@rm -f $(NAME)
			@echo "\033[1;31m$(NAME)\033[1;0m\033[31m Removed.\033[0m"

re: 		fclean $(NAME)
	
libft/libft.a:
			@make -C libft all