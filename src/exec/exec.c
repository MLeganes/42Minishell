/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:31:32 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/20 17:37:44 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_program(t_info *ms, int islast)
{
	int	fdp[2];

	if (isbuiltin(ms->tmp_pgm->argv) && !ms->npipes)
	{
		if (redir_selector(ms, 0))
			builtin_selector(ms, ms->tmp_pgm, 0);
	}
	else
	{
		if (pipe(fdp) == -1)
			error_exit_errno(127, "pipe", "error", 0);
		if (!ft_strncmp(ms->tmp_pgm->argv[0], "exit", 4) && ms->npipes)
		{
			exec_parent(ms, fdp, islast);
			return ;
		}
		ms->tmp_pgm->pid = fork();
		if (ms->tmp_pgm->pid < 0)
			error_exit_errno(errno, "fork", strerror(errno), 0);
		else if (ms->tmp_pgm->pid == 0)
			exec_child(ms, fdp);
		else
			exec_parent(ms, fdp, islast);
		ms->idx++;
	}
}

void	execute(t_info *ms)
{
	int	islast;

	ms->idx = 0;
	ms->tmp_pgm = ms->pgmlist;
	ms->fd_old[READ] = STDIN_FILENO;
	ms->fd_old[WRITE] = -1;
	ms->env = ms_env_to_arr(ms->env_v);
	while (ms->tmp_pgm)
	{
		islast = 0;
		if (!ms->tmp_pgm->next)
			islast = 1;
		if (ms->tmp_pgm->argv)
		{
			if (isbuiltin(ms->tmp_pgm->argv) == 0)
				env_search_program_path(ms, ms->tmp_pgm->argv[0]);
			if (ms->tmp_pgm->argv[0])
				exec_program(ms, islast);
		}
		ms->tmp_pgm = ms->tmp_pgm->next;
	}	
	parent_waitpid(ms);
	free_ms_env(ms);
}
