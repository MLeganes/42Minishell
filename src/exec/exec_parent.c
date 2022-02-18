/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/18 04:07:33 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* The WIFSIGNALED macro is always successful. */
/* If the child process for which status was returned by the wait or */
/* waitpid function exited because it raised a signal that caused it */
/* to exit, the WIFSIGNALED macro evaluates to TRUE and the WTERMSIG */
/* macro can be used to determine which signal was raised by the child*/
/* process. Otherwise, the WIFSIGNALED macro evaluates to FALSE. */
/*
	MAN SIGNAL
	No    Name         Default Action       Description
	1     SIGHUP       terminate process    terminal line hangup
	2     SIGINT       terminate process    interrupt program
	3     SIGQUIT      create core image    quit program
*/
void	parent_waitpid(t_info *ms)
{
	int	status;
	int ex;

	status = 0;
	while (ms->idx > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			{
			ex = WEXITSTATUS(status);
			errno = ex;
		}
		
		// if (WIFEXITED(status) == true)
		// {
		// 	printf("Parent IF status = %d G_exit_status: %d \n", status, g_exit_status);
		// 	g_exit_status = WEXITSTATUS(status);
		// }
		// else
		// {
		// 	printf("Parent ELSE status = %d G_exit_status: %d \n", status, g_exit_status);
		// 	g_exit_status = 127;
		// 	error_exit("cmd ", strerror(errno));
		// }
		// if (WIFSIGNALED(status))
		// {
		// 	printf("Parent WIF-SIGNAL status = %d G_exit_status: %d \n", status, g_exit_status);
		// 	if (WTERMSIG(status) == 3)
		// 		write(STDERR_FILENO, "Quit: 3\n", 8);
		// 	else if (WTERMSIG(status) == 2)
		// 		write(STDERR_FILENO, "\n", 1);
		// 	g_exit_status = 128 + WTERMSIG(status);
		// }
		ms->idx--;
	}
}

void	exec_parent(t_info *ms, int fd[2], int islast)
{
	signal(SIGINT, sig_fork);
	signal(SIGQUIT, sig_fork);
	if (ms->idx > 0)
		close(ms->fd_old[READ]);
	ms->fd_old[READ] = fd[READ];
	ms->fd_old[WRITE] = fd[WRITE];
	close(fd[WRITE]);
	if (islast)
		close(fd[READ]);
}
