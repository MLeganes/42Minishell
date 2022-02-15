/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/15 23:34:06 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_info *ms, int fd[2])
{	
	int		redirstatus;
	char	**env;

	if (ms->tmp_pgm->next)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
	}
	if (ms->fd_old[WRITE] != -1)
	{
		close(ms->fd_old[WRITE]);
		dup2(ms->fd_old[READ], STDIN_FILENO);
		close(ms->fd_old[READ]);
	}
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
