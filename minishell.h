/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:56:50 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/06 14:31:36 by amorcill         ###   ########.fr       */
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
/* ************************************************************************** */
/* USER INCLUDES															  */
/* ************************************************************************** */
# include "libft/libft.h"


/* ************************************************************************** */
/* STRUCT DEFS															  	  */
/* ************************************************************************** */
typedef struct s_info
{
	char		*cmdline;
	char		*prompt;
	t_token		*list;
	t_command	cmd;
} t_info;

typedef struct s_token
{
	int		flag;
	char	*token;
	t_token	*next;
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


/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

/*
 * MINISHELL
 */


# endif