/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:56:50 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/10 15:51:50 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/* STD LIBC INCLUDES														  */
/* ************************************************************************** */
# include <unistd.h> // systemcalls, execve
# include <stdlib.h> // exit
# include <stdio.h>	 // printf, fgets
# include <readline/readline.h>
# include <readline/history.h>

struct s_command;
struct s_token;
/* ************************************************************************** */
/* USER INCLUDES															  */
/* ************************************************************************** */
# include "libft/libft.h"

/* ************************************************************************** */
/* STRUCT DEFS															  	  */
/* ************************************************************************** */
enum type
{
	DLESS,
	DGREAT,
	LESS,
	GREAT,
	PIPE,
	DQUOTE,
	QUOTE,
} type;

typedef struct s_token
{
	enum type		type;
	char			*data;
	struct s_token	*next;
} t_token;


typedef struct s_command
{
	int		argc;
	char	*argv[128];
	enum	builtin 
	{
		NONE,
		QUIT,
		JOBS,
		BG,
		FG
	} builtin;
	char *name;
} t_command;

typedef struct s_info
{
	char		*cmdline;
	char		*prompt;
	t_token		*list;
	char		**args;
	t_command	cmd;
} t_info;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

/*
 * MINISHELL
 */

void lexer(t_info *info);

# endif