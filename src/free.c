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

void	free_env(t_info *ms)
{
	t_env	*actual;
	t_env	*next;

	if (ms->env_v != NULL)
	{
		actual = ms->env_v;
		while (actual != NULL)
		{
			next = actual->next;
			if (actual->var)
				free(actual->var);
			if (actual->content)
				free(actual->content);
			if (actual != NULL)
			{
				free(actual);
				actual = NULL;
			}
			actual = next;
		}
		ms->env_v = NULL;
		ms->tmp_env = NULL;
	}
}

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
static void free_redir(t_redir *rd)
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
	if (ms->tmp_pgm)
		free(ms->tmp_pgm);
	ms->tmp_pgm = NULL;
	if (ms->tmp_tkn)
		free(ms->tmp_tkn);
	ms->tmp_tkn = NULL;
}

void	free_end(t_info *ms)
{	
	if (ms->cmdline != NULL)
		free(ms->cmdline);
	free_list(ms);
	free_env(ms);
	free_pgmlist_end(ms);
	if (ms->tmp_pgm)
		free(ms->tmp_pgm);
	ms->tmp_pgm = NULL;
	if (ms->tmp_tkn)
		free(ms->tmp_tkn);
	ms->tmp_tkn = NULL;
}
