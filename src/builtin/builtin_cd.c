/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:33:33 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/05 22:35:29 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_info *ms, t_program *pgm)
{
	int	res;

	(void)ms;
	res = 0;
	if (pgm->argv[1])
		res = chdir(pgm->argv[1]);
	if (res == -1)
		printf("minishel: No such file or directory\n");
}
