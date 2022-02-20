/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/20 16:18:56 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_dup_close_fd(int fd[2])
{
	close(fd[READ]);
	dup2(fd[WRITE], STDOUT_FILENO);
	close(fd[WRITE]);
}

static void	ms_dup_close_fd_old(t_info *ms)
{
	close(ms->fd_old[WRITE]);
	dup2(ms->fd_old[READ], STDIN_FILENO);
	close(ms->fd_old[READ]);
}

void	exec_child(t_info *ms, int fd[2])
{
	int		redirstatus;
	int		res;

	if (ms->tmp_pgm->next)
		ms_dup_close_fd(fd);
	if (ms->fd_old[WRITE] != -1)
		ms_dup_close_fd_old(ms);
	redirstatus = redir_selector(ms, 1);
	if (isbuiltin(ms->tmp_pgm->argv) == 1 && redirstatus)
		builtin_selector(ms, ms->tmp_pgm, 1);
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		res = execve(ms->tmp_pgm->argv[0], ms->tmp_pgm->argv, ms->env);
		if (res < 0)
		{
			if (errno == EACCES)
				error_exit(ms->tmp_pgm->argv[0], " permission denied");
			else
				error_exit(ms->tmp_pgm->argv[0], " command not found");
			free_end(ms);
			g_exit_status = errno;
			exit(errno);
		}
	}
	// test if afect to PIPES
	// is not ending if there is a failed command
}
