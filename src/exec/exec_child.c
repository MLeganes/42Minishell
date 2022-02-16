/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/16 15:46:36 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exec_child_close_fd(int fd[2])
{
	close(fd[READ]);
	dup2(fd[WRITE], STDOUT_FILENO);
	close(fd[WRITE]);
}

static void	ms_exec_child_close_fd_old(t_info *ms)
{
	close(ms->fd_old[WRITE]);
	dup2(ms->fd_old[READ], STDIN_FILENO);
	close(ms->fd_old[READ]);
}

void	exec_child(t_info *ms, int fd[2])
{
	int		redirstatus;
	char	**env;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ms->tmp_pgm->next)
		ms_exec_child_close_fd(fd);
	if (ms->fd_old[WRITE] != -1)
		ms_exec_child_close_fd_old(ms);
	redirstatus = redir_selector(ms, 1);
	env = ms_env_to_arr(ms->tmp_env);
	if (isbuiltin(ms->tmp_pgm->argv) == 1 && redirstatus)
		builtin_selector(ms, ms->tmp_pgm);
	else
		execve(ms->tmp_pgm->argv[0], ms->tmp_pgm->argv, env);
	free(env);
	free_after_cmd(ms);
	exit(EXIT_FAILURE);
}
