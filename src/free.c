/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:21:55 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/20 18:12:13 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***
 * 
 *  parser is deleteing the ms.list!!!
 * 
 ***/
static void free_list(t_info *ms)
{
	t_token *actual;
	t_token *next;
	
	if (ms->list != NULL)
	{
		actual = ms->list;
		while ( actual != NULL)
		{
			next = actual->next;
			if (actual->data)
				free(actual->data);
			// if (actual->expansion)
			// 	free(actual->expansion);
			if (actual != NULL)
			 	free(actual);
			actual = next;
		}
		ms->list = NULL;
	}
}

static void free_argv(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if(argv[i] != NULL)
		free(argv[i]);
		i++;
		/* code */
	}
}

static void free_pgmlist(t_info *ms)
{
	t_program *actual;
	t_program *next;
	
	if (ms->pgmlist != NULL)
	{
		actual = ms->pgmlist;
		while ( actual != NULL)
		{
			next = actual->next;
			if (actual->argv)
			{
				free_argv(actual->argv);
			}
			if (actual != NULL)
			 	free(actual);
			actual = next;
		}
		ms->pgmlist = NULL;
	}
}

void free_after_cmd(t_info *ms)
{
	if (ms->cmdline != NULL)
		free(ms->cmdline);
	free_list(ms);
	free_pgmlist(ms);
	if (ms->tmp_pgm)
		free(ms->tmp_pgm);
	ms->tmp_pgm = NULL;
	if (ms->tmp_tkn)
		free(ms->tmp_tkn);
	ms->tmp_tkn = NULL;
}

void free_end(t_info *ms)
{	
	(void)ms;
	// free env!!!!
	
}

