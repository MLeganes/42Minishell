/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:56:50 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/03 14:58:26 by annarohmnn       ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>			// stat, fstat
# include <fcntl.h>				// O_RDONLY
# include <signal.h>			// signal

# include <sys/types.h>		// waitpid
# include <sys/wait.h>		// waitpid

# include <errno.h>			// errno

/* ************************************************************************** */
/* USER INCLUDES															  */
/* ************************************************************************** */
# include "../libft/libft.h"
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
	char	*var;			// name
	char	*content;		// value
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
	t_cmdname			name; //echo cd 
	pid_t				pid;
	char 				**argv; 	// agrv[0] cmd, agrv[1]   Everything after the command, echo "hola" or expanded env.
	int 				nargvs;	
	t_redir				*redir;		//redirections
	
	struct s_program	*next;
}						t_program;

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
	int 		fd[2];		// pipex
	int 		std_out;	// pipex
	int			npgms;
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

/*
 * LEXER: lexer_quotes
 */
void		quotes(t_info *info);

/*
 * PARSER: parser, program, redirection and heredoc.
 */
t_program	*new_program(void); // It will contain all command info, called here program.
void		ms_program_updatepath(t_info *ms);
void 		ms_program_lstadd_last(t_program **lst, t_program *new);
void		ms_program_argv_add(t_program *pgm, char *data);
void		parser_build_redirection(t_info *ms, t_program **pgm);
void		ms_redir_lstadd_last(t_program **pgm, t_redir *new);
void		ms_redir_heredoc(t_info *ms, t_program **pgm);
int			redir_selector(t_info *ms, int inb);
/*
 * ENVIRONMENT
 */
void	get_env(t_info *info, char **env);
int		ms_expand_get_len(char *s, int i);			// Used by here-doc
char	*ms_expand_get_value(t_info *ms, char *s, int i, int ret); // Used by here-doc

// Anna new function.
char	*ms_get_path(char **env, char *command);
t_env	*ms_new_env(char *var, char *content, t_env *next);

/*
 * SIGNAL
 */
void	signal_init(void);
void	signal_dfl(void);
void	signal_ctrlc_heredoc(void);

/*
 * EXECUTION
 */
void	exec_parent(t_info *ms, int fd[2], int islast);
void	exec_child(t_info *ms, int fd[2]);
/*
 * BUILTIN COMMANDS
 */
int		isbuiltin(char **argv);
void	builtin_selector(t_info *ms, t_program *pgm);
void	exec_echo(t_info *ms, t_program *pgm);
void	exec_cd(t_info *ms, t_program *pgm);
void	exec_pwd(t_info *ms, t_program *pgm);
void	exec_export(t_info *ms, t_program *pgm);
void	ms_print_export(t_env *env);
// void	exec_unset(t_info *ms, t_program *pgm);
// void	exec_env(t_info *ms, t_program *pgm);
// void	exec_exit(t_info *ms, t_program *pgm);

/*
 * PRINT
 */
void	print_env(t_info *ms);
void	print_quotes(t_info *ms);
void	print_lexer(t_info *ms);

/*
 * ERROR
 */

/*
 * FREE
 */
void	free_after_cmd(t_info *ms);
void	free_end(t_info *ms);
#endif
