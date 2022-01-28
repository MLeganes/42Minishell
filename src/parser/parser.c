/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:16 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/28 16:50:10 by amorcill         ###   ########.fr       */
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
	new->redir = NULL;
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
			 *  Redirection.
			 ***/
			parser_build_redirection(ms, &pgm);
		}
		ms->tmp_tkn = ms->tmp_tkn->next;
		/***
		 *  FREEEE token from t_info
		 * 
		 *  put in the free.c!!!!!!
		//free(ms->list->data);
		 ***/
	} // END-WHILE
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
