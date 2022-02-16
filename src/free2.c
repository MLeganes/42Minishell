/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:29:29 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/16 09:30:25 by annarohmnn       ###   ########.fr       */
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
			{
				free(actual->data);
				actual->data = NULL;
			}
			if (actual != NULL)
			{
				free(actual);
				actual = NULL;
			}
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
