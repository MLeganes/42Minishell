/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:59:43 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/09 09:37:31 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *arg, char *msg)
{
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 1;
}
