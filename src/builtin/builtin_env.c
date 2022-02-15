/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:37:54 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/15 19:47:34 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_info *ms)
{
	t_env	*token;

	token = ms->env_v;
	if (token == NULL)
	{
		error_exit(" env", "environtment not set");
		g_exit_status = 2;
		return ;
	}
	while (token != NULL)
	{
		printf("%s", token->var);
		printf("=");
		printf("%s", token->content);
		printf("\n");
		token = token->next;
	}
}
