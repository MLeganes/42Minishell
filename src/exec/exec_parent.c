/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/20 20:52:09 by arohmann         ###   ########.fr       */
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
	int	ex;

	status = 0;
	while (ms->idx > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			ex = WEXITSTATUS(status);
			errno = ex;
			g_exit_status = errno;
			if (errno == 2)
				g_exit_status = 127;
		}
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
