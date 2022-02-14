/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:21:55 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/14 13:47:09 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_info *ms)
{
	t_token	*actual;
	t_token	*next;

	if (ms->list != NULL)
	{
		actual = ms->list;
		while (actual != NULL)
		{
			next = actual->next;
			if (actual->data)
				free(actual->data);
			if (actual != NULL)
				free(actual);
			actual = next;
		}
		ms->list = NULL;
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv != NULL)
	{
		while (argv[i])
		{
			if (argv[i] != NULL)
				free(argv[i]);
			i++;
		}
		free(argv);
	}
}

/* static void	free_pgmlist(t_info *ms)
{
	t_program	*actual;
	t_program	*next;

	if (ms->pgmlist != NULL)
	{
		actual = ms->pgmlist;
		while (actual != NULL)
		{
			next = actual->next;
			if (actual->argv)
				free_argv(actual->argv);
			if (actual != NULL)
				free(actual);
			actual = next;
		}
		ms->pgmlist = NULL;
	}
} */

static void	free_pgmlist_end(t_info *ms)
{
	t_program	*actual;
	t_program	*next;

	if (ms->pgmlist != NULL)
	{
		actual = ms->pgmlist;
		while (actual != NULL)
		{
			next = actual->next;
			if (actual->argv)
			{
				free_argv(actual->argv);
			}
			if (actual->redir)
			{
				if(actual->redir->file)
					free(actual->redir->file);
				free(actual->redir);
			}
			if (actual != NULL)
				free(actual);
			actual = next;
		}
		ms->pgmlist = NULL;
	}
}

void	free_after_cmd(t_info *ms)
{
	if (ms->cmdline != NULL)
		free(ms->cmdline);
	free_list(ms);
	free_pgmlist_end(ms);
	if (ms->tmp_pgm)
		free(ms->tmp_pgm);
	ms->tmp_pgm = NULL;
	if (ms->tmp_tkn)
		free(ms->tmp_tkn);
	ms->tmp_tkn = NULL;
}

void	free_end(t_info *ms)
{	
	free_pgmlist_end(ms);
}
