/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:16 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/20 12:56:25 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_program *new_program()
{
	t_program *new;
	
	new = (t_program *)malloc(sizeof(t_program));
	if (new == NULL)
		return (NULL);
	new->name = CMD_NONE;
	new->argv = NULL;
	new->nargvs = 0;
	new->homedir = NULL;
	new->next = NULL;
	return (new);
}

static t_program *ms_program_lstlast(t_program *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void ms_program_lstadd_last(t_program **lst, t_program *new)
{
	t_program *last;
	
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ms_program_lstlast(*lst);
		if (last)
			last->next = new;
	}
}

// static void ms_cmd_case_echo(t_info *ms, t_token *tk)
// {
// 	(void)ms;
// 	tk->cmdname = CMD_ECHO;
// 	// path = env(cd)
// 	// path = env(pwd)
	
// 	printf("Command is echo cmdname: %d\n", tk->cmdname);
// }

// static void ms_cmd_case_cd(t_info *ms, t_token *tk)
// {
// 	t_program *p;

// 	tk->cmdname = CMD_CD;
// 	p = new_program();
// 	if ( p == NULL)
// 		return ;
// 	p->name = CMD_CD;
// 	p->argv = (char **) malloc(sizeof(char **) * 2); // protection!!
// 	p->argv[0] = ft_strdup("cd");
// 	if (tk->next == NULL)
// 		p->argv[1] = NULL;
// 	else
// 	{
// 		// WARNING::
// 		// NO MALLOC -- copy ref to pointer DATA!!!!!!!
// 		p->argv[1] = tk->next->data; //path to change
// 	}	
// 	// p->option; //no needed
// 	// p->path;   //no needed	
// 	ms_program_lstadd_last(&ms->pgmlist, p);
	
// 	printf("Command is cd cmdname: %d\n", tk->cmdname);
// }

// // static void ms_cmd_case_pwd(t_info *ms, t_token *tk)
// // {
	
// // }

// static void	ms_cmd_selector(t_info *ms, t_token *tk)
// {
// 	if (ft_strncmp(tk->data, "echo", 4) == 0)
// 		ms_cmd_case_echo(ms, tk);
// 	else if (ft_strncmp(tk->data, "cd", 2) == 0)
// 		ms_cmd_case_cd(ms, tk);
// 	//else if (ft_strncmp(tk->data, "pwd", ft_strlen(tk->data)) == 0)
// 	//	ms_cmd_case_pwd(ms, tk);
// 	// else if (ft_strncmp(tk->data, "export", ft_strlen(tk->data)) == 0)
// 	// 	ms_cmd_case_export(ms);	
// 	// else if (ft_strncmp(tk->data, "unset", ft_strlen(tk->data)) == 0)
// 	// 	ms_cmd_case_unset(ms);
// 	// else if (ft_strncmp(tk->data, "env", ft_strlen(tk->data)) == 0)
// 	// 	ms_cmd_case_env(ms);
// 	// else if (ft_strncmp(tk->data, "exit", ft_strlen(tk->data)) == 0)
// 	// 	ms_cmd_case_exit(ms);
// }


static void	ms_program_argv_add(t_program *pgm, char *data)
{
	char	**new;
	int		i;

	i = 0;
	if(!pgm->argv)
		new = malloc(sizeof(char *) * 2);
	else
		new = malloc(sizeof(char *) * (pgm->nargvs + 2));
	while (pgm->argv && pgm->argv[i])
	{
		new[i] = pgm->argv[i];
		i++;
	}
	new[i] = ft_strdup(data);
	i++;
	new[i] = NULL;	
	if (pgm->argv)
		free(pgm->argv);
	pgm->argv = new;
	pgm->nargvs++;
}

static void	parser_build_program(t_info *ms)
{
	t_program	*pgm;

	// create new program-cmd
	pgm = new_program();
	if ( pgm == NULL)
		return ;
	while ( ms->tmp_tkn && ms->tmp_tkn->type != PIPE)
	{
		if (ms->tmp_tkn->type == TOKEN)
			ms_program_argv_add(pgm, ms->tmp_tkn->data);	//append
		else if (ms->tmp_tkn->type == REDIR_DGREAT || ms->tmp_tkn->type == REDIR_DLESS 
			|| ms->tmp_tkn->type == REDIR_GREAT || ms->tmp_tkn->type == REDIR_LESS)
		{
			/***
			 *  parser_build_redirection(...)
			 *  to do something wiht redirrrrr!!!
			 *  For Anna :)
			 * 
			 ***/
		}
		ms->tmp_tkn = ms->tmp_tkn->next;
		/***
		 *  FREEEE token from t_info
		 * 
		 *  put in the free.c!!!!!!
		//free(ms->list->data);
		 ***/
	}//END-WHILE
		//if (ms->list && ms->list->type == PIPE)
			//stop. new program
	ms_program_lstadd_last(&ms->pgmlist, pgm);
	ms->npgms++;
}

void	parser(t_info *ms)
{
	//2nd try!!
	// token list
	// free the ms.list!!!!
	ms->tmp_tkn = ms->list;
	
	while (ms->tmp_tkn)
	{
		parser_build_program(ms);
		// if (ms->list && ms->list->next)
		// 	free(ms->list->data);
		if (ms->tmp_tkn)
			ms->tmp_tkn = ms->tmp_tkn->next;
	}
	// check what to free!!!
}
