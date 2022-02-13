/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:56:50 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/13 20:58:40 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/***************************************************************************/
/* STD LIBC INCLUDES													   */
/***************************************************************************/
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <termios.h>
/* ************************************************************************** */
/* USER INCLUDES															  */
/* ************************************************************************** */
# include "../libft/libft.h"
# include <stdbool.h>
/* ************************************************************************** */
/* COLORS																	..*/
/* ************************************************************************** */
# define GREEN		"\033[32m"
# define RED		"\033[35m"
# define RE			"\033[0m"

# define ERROR		-1
# define READ		0
# define WRITE		1

/* ************************************************************************** */
/* STRUCT DEFS															  	  */
/* ************************************************************************** */
int	g_exit_status;
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
	CHAR_VAR = '$',
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
	CMD_REDIR,
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
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	int				is_out;
	int				is_app;
	struct s_redir	*next;
}	t_redir;

/***
 *
 * Struct to keep the program (cmd) to execute.
 *
 ***/
typedef struct s_program
{
	pid_t				pid;
	char				**argv;
	int					nargvs;
	t_redir				*redir;
	struct s_program	*next;
}	t_program;

typedef struct s_heredoc
{
	char	*delim;
	char 	*file;
	char 	*line;
	int 	fd;
	int 	fd_stdin;
	int 	exit;
	int		del_qu;
}	t_heredoc;

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
	char		**env;
	char		*cmdline;
	char		*prompt;
	t_token		*list;
	t_token		*tmp_tkn;
	char		tmp_c;
	int			ntok;
	int			npipes;
	int			error;
	t_program	*pgmlist;
	t_program	*tmp_pgm;
	int			fd_old[2];
	int			std_out;
	int			npgms;
}	t_info;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

/*
 * MINISHELL
 */
int			lexer(t_info *info);
int			parser(t_info *ms);
void		execute(t_info *ms);
int			expansion(t_info *ms);
/*
 * LEXER: lexer_quotes
 */
int			quotes(t_info *info);
int			expansion(t_info *ms);
int			ms_chartype(char c);
t_token		*new_tok(int len);
char		*ms_append_char(char *str, char c);
void		ms_state_selector(t_info *ms, int chartype);
void		ms_case_endtoken(t_info *ms);
void		ms_case_multiple(t_info *ms, int chartype);
void		ms_case_redirect(t_info *ms, int chartype);
int			ms_exp_var(t_info *ms, char **tmp, char *str, int *i);
void		ms_end_tmp(char **tmp, int *i);
/*
 * PARSER: parser, program, redirection and heredoc.
 */
t_program	*new_program(void);
void		ms_program_updatepath(t_info *ms);
void		ms_program_lstadd_last(t_program **lst, t_program *new);
void		ms_program_argv_add(t_program *pgm, char *data);
int			parser_build_redirection(t_info *ms, t_program **pgm);
void		ms_redir_lstadd_last(t_program **pgm, t_redir *new);
int			ms_redir_heredoc(t_info *ms, t_program **pgm);
int			redir_selector(t_info *ms, int inb);
/*
 * ENVIRONMENT
 */
void		get_env(t_info *info, char **env);
int			ms_expand_get_len(char *s, int i);
char		*ms_expand_get_value(t_info *ms, char *s, int i, int ret);
t_env		*ms_find_env_var(t_info *ms, char **var);
char		**ms_env_to_arr(t_env *env);
char		*ms_get_path(char **env, char *command);
t_env		*ms_new_env(char *var, char *content, t_env *next);

/*
 * SIGNAL
 */
void		signalhandler_ctrlc(int sig);
void		signalhandler_heredoc(int sig);

/*
 * EXECUTION
 */
void		exec_parent(t_info *ms, int fd[2], int islast);
void		exec_child(t_info *ms, int fd[2]);
void		parent_waitpid(t_info *ms);
/*
 * BUILTIN COMMANDS
 */
int			isbuiltin(char **argv);
void		builtin_selector(t_info *ms, t_program *pgm);
void		exec_echo(t_info *ms, t_program *pgm);
void		exec_cd(t_info *ms, t_program *pgm);
void		exec_pwd(t_info *ms, t_program *pgm);
void		exec_export(t_info *ms, t_program *pgm);
void		export_print(t_info *ms, t_env *env);
void		exec_unset(t_info *ms, t_program *pgm);
void		exec_unset(t_info *ms, t_program *pgm);
void		exec_env(t_info *ms);
int			exec_exit(t_program *pgm);

/*
 * PRINT
 */
void		print_env(t_info *ms);
void		print_quotes(t_info *ms);
void		print_lexer(t_info *ms);

/*
 * ERROR
 */
void		error_exit(char *arg, char *msg);
/*
 * FREE
 */
void		free_after_cmd(t_info *ms);
void		free_end(t_info *ms);
void		free_argv(char **argv);
void		free_list(t_info *ms);
#endif
