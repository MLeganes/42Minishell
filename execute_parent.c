/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:02 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/21 17:08:29 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_parent(t_info *ms, int fd[2], int old_fd[2],int islast)
{
	signal(SIGINT, ms_signal_fork);
	signal(SIGQUIT, ms_signal_fork);
	if (ms->idx > 0)
		close(old_fd[READ]);
	old_fd[READ] = fd[READ];
	old_fd[WRITE] = fd[WRITE];
	close(fd[WRITE]);
	if (islast) //last command. 
		close(fd[READ]);
}