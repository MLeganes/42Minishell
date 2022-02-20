/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:45:59 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/20 16:06:06 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_program *pgm)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	while (pgm->argv[i] != NULL && ft_strncmp(pgm->argv[i], "-n", 3) == 0)
	{
		i++;
		flag = 1;
	}
	while (pgm->argv[i])
	{
		ft_putstr_fd(pgm->argv[i], STDOUT_FILENO);
		if (pgm->argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
		g_exit_status = 0;
	}
	if (flag != 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
