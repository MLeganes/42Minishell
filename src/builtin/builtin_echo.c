/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:45:59 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/19 21:42:58 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_word_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

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
		i++;
		if (i < ft_word_count(pgm->argv))
			ft_putstr_fd(" ", STDOUT_FILENO);
		// if (pgm->argv[i + 1])
		// 	ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag != 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
