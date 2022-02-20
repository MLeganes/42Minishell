/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:28:44 by arohmann          #+#    #+#             */
/*   Updated: 2022/02/20 20:11:48 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_status(char **args, int ret)
{
	ret = ft_atoi(args[1]);
	if (ret > 255)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 6);
		exit(ret % 256);
	}
	else if (ret < 0)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 6);
		exit (ret + 256);
	}
	else
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 6);
		exit(ret);
	}
}

static int	exit_args(t_program *pgm)
{
	ft_putstr_fd("exit\n", 2);
	error_exit(pgm->argv[0], " too many arguments");
	g_exit_status = 1;
	return (1);
}

int	exec_exit(t_program *pgm)
{
	int	i;

	i = 0;
	if (pgm->argv[1] == NULL)
		exit(g_exit_status);
	if (pgm->argv[2] != NULL)
		return (exit_args(pgm));
	if ((pgm->argv[1][i] == '+' || pgm->argv[1][i] == '-'))
		i++;
	while (((ft_strcmp(pgm->argv[1], "") == 0) || pgm->argv[1][i] != '\0' ))
	{
		if ((pgm->argv[1][i] != '+' || pgm->argv[1][i] != '-')
				&& ft_isdigit(pgm->argv[1][i]) != 1)
		{
			ft_putstr_fd("exit\n", 2);
			error_exit(pgm->argv[0], " numeric argument required");
			exit(255);
		}
		i++;
	}
	ms_exit_status(pgm->argv, 0);
	return (0);
}
