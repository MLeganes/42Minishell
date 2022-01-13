/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:56:50 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/13 15:26:45 by arohmann         ###   ########.fr       */
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
/* COLORS															  */
/* ************************************************************************** */
#define GREEN	"\033[32m"
#define RED		"\033[35m"
#define RE		"\033[0m"
/* ************************************************************************** */
/* STRUCT DEFS															  	  */
/* ************************************************************************** */
enum type
{
	REDIR_DLESS = 1000,
	REDIR_DGREAT,
	REDIR_LESS,
	REDIR_GREAT,
	PIPE,
	SEMICOLON,
	AMPERSAND,
	DQUOTE,
	QUOTE,	
	TOKEN,
	DOLLAR,	
	REDIR_VOID,		// If the input for the simpre command is just an immediate EOF.
};


// New token type for lexer. I just copy, to be faster. It is duplicated now.
enum CharType{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = '\0',
};


// State of the lexer, when it is checking the char by char.
enum {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,	
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
};

typedef struct s_token
{
	int 			len;
	char			*data;
	int				type;			// 	WORD, OPERATOR, 
	char			*expansion;		//When there is a " $USER BLA BLA BLA ..." for type DQUOUTE or QUOUTE
	struct s_token	*next;
} 					t_token;

typedef struct s_info
{
	int 		idx;
	char		*cmdline;
	char		*prompt;
	t_token		*list;
	char 		tmp_c;
	t_token 	*tmp_tkn;
	int			ntok;
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

void	lexer(t_info *info);

/*
 * FREE
 */
void	free_after_cmd(t_info *ms);

# endif