/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:37:54 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/06 12:38:37 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_info *ms)
{
	t_env	*token;

	token = ms->env_v;
	while (token != NULL)
	{
		printf("%s", token->var);
		printf("=");
		printf("%s", token->content);
		printf("\n");
		token = token->next;
	}
}
