/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:33:33 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/11 12:15:25 by arohmann         ###   ########.fr       */
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
	}
	if (res == -1)
	{
		perror("minishell: cd");
	}
}
