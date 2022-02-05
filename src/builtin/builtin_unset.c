/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:58:59 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/05 20:59:01 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ms_free_str(char **str)
{
	free(*str);
	*str = NULL;
}

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
			ms_free_str(&current->var);
			ms_free_str(&current->content);
			free(current);
			current = NULL;
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	exec_unset(t_info *ms, t_program *pgm)
{
	int i;
	int	j;
	char	*var;

	i = 1;
	while (pgm->argv[i])
	{
		j = 0;
		while (pgm->argv[i][j] != '=')
			j++;
		var = ft_substr(pgm->argv[i], 0, (j - 1));
		if (ms_find_env_var(ms, &var) != NULL)
		{
			ms_del_env_var(&ms->env_v, var);
		}
		else
			printf("\t");
		i++;
	}
	return ;
}