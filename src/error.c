/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:59:43 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/06 14:04:16 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//free everything before exit!
//Or maybe no exit, just print promt 
//exit (EXIT_FAILURE);
void	error_exit(t_info ms)
{
	printf("Error ocurred while executing bash!\n");
}
