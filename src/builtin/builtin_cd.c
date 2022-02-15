/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:33:33 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/15 19:41:41 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_info *ms, t_program *pgm)
{
	int	res;

	(void)ms;
	res = 0;
	if (pgm->argv[1])
	{
		res = chdir(pgm->argv[1]);
		g_exit_status = 0;
	}
	if (res == -1)
	{
		g_exit_status = 2;
		perror("minishell: cd");
	}
}
