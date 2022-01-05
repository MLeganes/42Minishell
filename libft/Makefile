# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/23 12:57:35 by amorcill          #+#    #+#              #
#    Updated: 2021/12/01 17:30:11 by amorcill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Werror -Wextra -g

SRCS = 	ft_atoi.c		ft_isalnum.c    ft_isdigit.c    ft_lstnew.c     ft_memcmp.c     ft_memset.c \
		ft_putnbr_fd.c  ft_strchr.c     ft_strjoin.c    ft_strlen.c     ft_strnstr.c    ft_substr.c \
		ft_bzero.c      ft_isalpha.c    ft_isprint.c    ft_memcpy.c     ft_putchar_fd.c ft_putstr_fd.c \
		ft_strdup.c     ft_strlcat.c    ft_strmapi.c    ft_strrchr.c    ft_tolower.c	ft_calloc.c \
		ft_isascii.c    ft_itoa.c       ft_memchr.c     ft_memmove.c    ft_putendl_fd.c ft_split.c \
		ft_striteri.c   ft_strlcpy.c    ft_strncmp.c    ft_strtrim.c    ft_toupper.c 	ft_atoi_ext.c \
		get_next_line.c get_next_line_utils.c \
		ft_printf.c    ft_printf_d.c  ft_printf_p.c  	ft_printf_arg.c  ft_printf_s.c  ft_printf_hex.c\
		ft_printf_u.c \
		
BONUS = ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c ft_lstlast.c	 ft_lstadd_back.c \
		ft_lstdelone.c	ft_lstclear.c	ft_lstiter.c	ft_lstmap.c	\

all: $(NAME) bonus

$(NAME):
	gcc $(CFLAGS) -c $(SRCS)
	ar -crs $(NAME) *.o

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

bonus: 
	gcc $(CFLAGS) -c $(BONUS) 
	ar -crs $(NAME) *.o
