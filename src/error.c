/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:59:43 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/09 13:50:31 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//free everything before exit!
//Or maybe no exit, just print promt 
//exit (EXIT_FAILURE);
void	error_exit(char *arg, char *msg)
{
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 1;
}
