/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:31:32 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/06 12:07:21 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_program(t_info *ms, int islast)
{
	int	fdp[2];

	if (isbuiltin(ms->tmp_pgm->argv) && !ms->npipes)
	{
		if (redir_selector(ms, 0))
			builtin_selector(ms, ms->tmp_pgm);
	}
	else
	{
		if (pipe(fdp) == -1)
			printf("Pipe Error \n");
		ms->tmp_pgm->pid = fork();
		if (ms->tmp_pgm->pid < 0)
			printf("Error in fork pid");
		else if (ms->tmp_pgm->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			exec_child(ms, fdp);
		}
		else
			exec_parent(ms, fdp, islast);
		ms->idx++;
	}
}

static void	update_fd(t_info *ms)
{
	if (ms->idx > 0)
	{
		dup2(ms->fd_bak[READ], STDIN_FILENO);
		dup2(ms->fd_bak[WRITE], STDOUT_FILENO);
	}
}

void	execute(t_info *ms)
{
	int	islast;

	ms->idx = 0;
	ms->tmp_pgm = ms->pgmlist;
	ms->fd_old[READ] = STDIN_FILENO;
	ms->fd_old[WRITE] = -1;
	while (ms->tmp_pgm)
	{
		islast = 0;
		if (!ms->tmp_pgm->next)
			islast = 1;
		if (ms->tmp_pgm->argv)
		{
			update_fd(ms);
			if (isbuiltin(ms->tmp_pgm->argv) == 0)
				ms_program_updatepath(ms);
			if (ms->tmp_pgm->argv[0])
				exec_program(ms, islast);
		}
		ms->tmp_pgm = ms->tmp_pgm->next;
	}
}
