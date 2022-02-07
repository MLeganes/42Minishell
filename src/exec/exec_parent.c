/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/06 12:07:44 by annarohmnn       ###   ########.fr       */
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
static void	parent_waitpid(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			write(STDERR_FILENO, "Quit: 3\n", 8);
		else if (WTERMSIG(status) == 2)
			write(STDERR_FILENO, "\n", 1);
		status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
}

void	exec_parent(t_info *ms, int fd[2], int islast)
{
	if (ms->idx > 0)
		close(ms->fd_old[READ]);
	ms->fd_old[READ] = fd[READ];
	ms->fd_old[WRITE] = fd[WRITE];
	close(fd[WRITE]);
	if (islast)
		close(fd[READ]);
	parent_waitpid(ms->tmp_pgm->pid);
	ms->idx--;
}
