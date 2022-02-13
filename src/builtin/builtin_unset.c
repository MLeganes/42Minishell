/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:58:59 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/13 21:35:41 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_del_env_var(t_env **env, char *var)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->var, var, ft_strlen(var) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			if (current->content)
			{
				free(current->content);
				current->content = NULL;
			}
			if (current->var)
			{
				free(current->var);
				current->var = NULL;
			}
			if (current)
			{
			free(current);
			current = NULL;
			}
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	exec_unset(t_info *ms, t_program *pgm)
{
	int		i;
	int		j;
	char	*var;

	i = 1;
	while (pgm->argv[i])
	{
		j = 0;
		if (ft_strcmp(pgm->argv[i], "") == 0)
		{
			error_exit("unset", "No such file or directory");
			return ;
		}
		while (pgm->argv[i][j] != '\0')
			j++;
		var = ft_substr(pgm->argv[i], 0, j);
		if (ms_find_env_var(ms, &var) != NULL)
		{
			ms_del_env_var(&ms->env_v, var);
		}
		else
			error_exit(" unset", " No such file or directory");
		i++;
	}
	if (var)
		free(var);
	return ;
}
