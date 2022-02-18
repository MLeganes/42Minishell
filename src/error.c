/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:59:43 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/18 02:24:57 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	error_exit_status127(char *argv)
{
	error_exit(argv, "No such file or directory");
	g_exit_status = 127;
	return (ERROR);
}

void	error_exit_errno(int errornum, char *arg, char *msg, int ms_exit)
{
	//write(1, "minishell: ", 11);
	//write(1, errormsg, ft_strlen(errormsg));
	///write(1, "\n", 1);
	errno = errornum;
	if (ms_exit == 1)
		exit(errornum);
	error_exit(arg, msg);
}