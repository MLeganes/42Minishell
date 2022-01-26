/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:56:50 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/27 00:07:47 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/* STD LIBC INCLUDES														  */
/* ************************************************************************** */
# include <unistd.h>			// systemcalls, execve
# include <stdlib.h>			// exit, getenv
# include <stdio.h>				// printf, fgets
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>			// stat, fstat
# include <fcntl.h>				// O_RDONLY
# include <signal.h>			// signal

# include <sys/types.h>		// waitpid
# include <sys/wait.h>		// waitpid

/* ************************************************************************** */
/* USER INCLUDES															  */
/* ************************************************************************** */
# include "libft/libft.h"
# include <stdbool.h>
/* ************************************************************************** */
/* COLORS															  */
/* ************************************************************************** */
# define GREEN	"\033[32m"
# define RED		"\033[35m"
# define RE		"\033[0m"
/* ************************************************************************** */
/* STRUCT DEFS															  	  */
/* ************************************************************************** */

# define READ 0 //STDIN_FILENO
# define WRITE 1

/***
 * If the input for the simple command is just an immediate EOF.
 ***/
typedef enum e_type
{
	REDIR_DLESS = 1000,
	REDIR_DGREAT,
	REDIR_LESS,
	REDIR_GREAT,
	PIPE,
	AMPERSAND,
	IN_DQUOTE,
	IN_QUOTE,	
	TOKEN,
	DOLLAR,	
	REDIR_VOID,
	NONE,
}	t_type;

// New token type for lexer. I just copy, to be faster. It is duplicated now.
typedef enum e_chartype{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = '\0',
}			t_chartype;

// State of the lexer, when it is checking the char by char.
typedef enum e_state{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,	
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
}	t_state;

typedef enum e_cmdname
{
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_REDIR,	//
	CMD_NONE,
	CMD_NO_FOUND,	
}		t_cmdname;

/***
 * 
 * type:		used in lexer.
 * cmdname: 	used in parser, used to indicate the command-program-name
 * expansion:	When there is a " $USER BLA BLA BLA ..." for type DQUOUTE or QUOUTE
 * 
 * 
 ***/
typedef struct s_token
{
	int				len;
	char			*data;
	t_type			type;
	t_cmdname		cmdname;
	int				in_q;
	int				in_dq;
	char			*expansion;
	struct s_token	*next;
	
}					t_token;

typedef struct s_env
{
	char	*var;
	char	*content;
	struct s_env	*next;
}	t_env;

/***
 *
 * Struct to keep the program (cmd) to execute.
 *
 ***/
typedef struct s_program
{
	t_cmdname			name; //echo cd 
	pid_t				pid;
	char 				**argv; 	// agrv[0] cmd, agrv[1]   Everything after the command, echo "hola" or expanded env.
	int 				nargvs;	
	char 				*homedir;
	
	struct s_program	*next;
}						t_program;

typedef struct s_redir
{
	char			*name;
	int				is_out;
	int				is_app;
	struct s_dedir	*next;
}	t_redir;

/***
 * state = LEXER to know what are you reading. 
 *   For ex. if you start reading " need to read until you  find another ", or '.
 * 
 * pgmlist = list of program-cmd to exucute
 * 
***/
typedef struct s_info
{
	int			idx;
	t_state		state;
	t_env		*env_v;
	t_env		*tmp_env;
	char		*cmdline;
	char		*prompt;
	t_token		*list; //Token form Lexer.
	t_token		*tmp_tkn;
	char		tmp_c;
	int			ntok;
	int			npipes;
	int 		error;
	t_program	*pgmlist;
	t_program	*tmp_pgm;
	int 		fd_old[2];	// pipex
	int 		fd_bak[2];	// pipex
	int 		fd[2];	// pipex
	int 		std_out;	// pipex
	int			npgms;
	t_redir		*redir;
	char 		**env_ptr_copy; //	
}				t_info;


/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

/*
 * MINISHELL
 */

void	lexer(t_info *info);
void	parser(t_info *ms);
void	execute(t_info *ms);
void	exec_parent(t_info *ms, int fd[2], int islast);
void	exec_child(t_info *ms, int fd[2]);

void	get_env(t_info *info, char **env);
int		get_env_pgmpath(t_info *ms, char *pgmname); // (*) same func. check for one
int		get_env_path(t_info *ms);					// (*) same func. check for one

/*
 * SIGNAL
 */
void	ms_signal_activate(void);
void	ms_signal_desactivate(void);

/*
 * BUILTIN COMMANDS
 */
int		ms_isbuiltin(char **argv);
void	ms_select_builtin(t_info *ms, t_program *pgm);
void	ms_pwd(t_info *ms, t_program *pgm);
void	ms_cd(t_info *ms, t_program *pgm);
void	ms_echo(t_info *ms, t_program *pgm);

/*
 * FREE
 */
void	free_after_cmd(t_info *ms);
void	free_end(t_info *ms);
#endif
