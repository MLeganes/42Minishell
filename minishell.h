/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:56:50 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/11 16:56:26 by amorcill         ###   ########.fr       */
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
	
	WORD,
	OPERATOR,	// 
	
	
	REDIR_IN,		// < repited!!
	REDIR_OUT,		// >
	REDIR_HEREDOC,	// <<
	REDIR_APPEND,	// >>
	REDIR_VOID,		// If the input for the simpre command is just an immediate EOF.
	
	
};

typedef struct s_token
{
	char			*data;
	int				type;			// 	WORD, OPERATOR, 
	char			*expansion;		//When there is a " $USER BLA BLA BLA ..." for type DQUOUTE or QUOUTE
	struct s_token	*next;
} 					t_token;

typedef struct s_info
{
	char		*cmdline;
	char		*prompt;
	t_token		*list;
	char		**args;
	int			state;		// LEXER to know what are you reading. 
							// For ex. if you start reading " need to read 
							// until you  find another ", or ' 
}				t_info;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

/*
 * MINISHELL
 */

void lexer(t_info *info);

# endif