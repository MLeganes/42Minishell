/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:48:55 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/18 00:29:06 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	*new_program(void)
{
	t_program	*new;

	new = (t_program *)malloc(sizeof(t_program));
	if (new == NULL)
		return (NULL);
	new->argv = NULL;
	new->pid = -1;
	new->nargvs = 0;
	new->next = NULL;
	new->redir = NULL;
	return (new);
}

// int	ms_program_updatepath(t_info *ms)
// {
// 	char	*path;

// 	path = ms_get_path(ms->env, ms->tmp_pgm->argv[0]);
// 	if (path != NULL)
// 	{
// 		if (ms->tmp_pgm->argv[0])
// 			free(ms->tmp_pgm->argv[0]);
// 		ms->tmp_pgm->argv[0] = path;
// 	}
// 	else
// 	{
// 		error_exit(ms->tmp_pgm->argv[0], " command not found");
// 		g_exit_status = 127;
// 		return (ERROR);
// 	}
// 	return (0);
// }

static t_program	*ms_program_lstlast(t_program *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ms_program_lstadd_last(t_program **lst, t_program *new)
{
	t_program	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ms_program_lstlast(*lst);
		if (last)
			last->next = new;
	}
}

void	ms_program_argv_add(t_program *pgm, char *data)
{
	char	**new;
	int		i;

	i = 0;
	if (!pgm->argv)
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
