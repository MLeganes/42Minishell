/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:10:15 by arohmann          #+#    #+#             */
/*   Updated: 2022/02/20 17:11:28 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fds_copy(t_info *ms)
{
	ms->fd_copy[0] = dup(STDIN_FILENO);
	ms->fd_copy[1] = dup(STDOUT_FILENO);
}

void	fds_reset(t_info *ms)
{
	dup2(ms->fd_copy[0], STDIN_FILENO);
	dup2(ms->fd_copy[1], STDOUT_FILENO);
}
