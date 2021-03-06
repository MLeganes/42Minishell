/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:21:55 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/16 09:39:15 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv != NULL)
	{
		while (argv[i] && ft_strlen(argv[i]) > 0)
		{
			if (argv[i] != NULL && ft_strlen(argv[i]) > 0)
				free(argv[i]);
			i++;
		}
		if (argv)
			free(argv);
	}
}

static void	free_redir(t_redir *rd)
{
	t_redir	*actual;
	t_redir	*next;

	if (rd != NULL)
	{
		actual = rd;
		while (actual != NULL)
		{
			next = actual->next;
			if (actual->file)
			{
				if (actual->type == REDIR_DLESS)
				{
					unlink(actual->file);
					free(actual->file);
				}
				actual->file = NULL;
			}
			if (actual)
				free(actual);
			actual = next;
		}
		rd = NULL;
	}
}

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
				free_redir(actual->redir);
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
}

void	free_end(t_info *ms)
{	
	rl_clear_history();
	if (ms->cmdline != NULL)
		free(ms->cmdline);
	free_list(ms);
	free_env(ms);
	free_pgmlist_end(ms);
	ms->tmp_pgm = NULL;
	if (ms->tmp_tkn)
		free(ms->tmp_tkn);
	ms->tmp_tkn = NULL;
}
