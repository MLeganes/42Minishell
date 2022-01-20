/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:45:59 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/20 16:09:02 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_echo(t_info *ms, t_program *pgm)
{
	(void)ms;
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (ft_strncmp(pgm->argv[i], "-n", 2) == 0 && pgm->argv[i] != NULL)
	{
		i++;
		flag = 1;
	}
	
	// code missing

	if (flag == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ms_echo(t_info *ms, t_program *pgm)
{
	exec_echo(ms, pgm);
}