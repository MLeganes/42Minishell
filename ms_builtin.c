/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:18:16 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/21 17:37:14 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_isbuiltin(char **argv)
{
	if (ft_strlen(argv[0]) == 3 && !ft_strncmp(argv[0], "pwd", 3))
		return (1);
	else if (ft_strlen(argv[0]) == 2 && !ft_strncmp(argv[0], "cd", 2))
		return (1);
	else if (ft_strlen(argv[0]) == 4 && !ft_strncmp(argv[0], "echo", 4))
		return (1);
	else if (ft_strlen(argv[0]) == 3 && !ft_strncmp(argv[0], "env", 3))
		return (1);
	else if (ft_strlen(argv[0]) == 6 && !ft_strncmp(argv[0], "export", 6))
		return (1);
	else if (ft_strlen(argv[0]) == 5 && !ft_strncmp(argv[0], "unset", 5))
		return (1);
	else if (ft_strlen(argv[0]) == 4 && !ft_strncmp(argv[0], "exit", 4))
		return (1);
	return (0);
}

void	ms_select_builtin(t_info *ms, t_program *pgm)
{
	if (ft_strlen(pgm->argv[0]) == 3 && !ft_strncmp(pgm->argv[0], "pwd", 3))
		ms_pwd(ms, pgm);
	else if (ft_strlen(pgm->argv[0]) == 2 && !ft_strncmp(pgm->argv[0], "cd", 2))
		ms_cd(ms, pgm);
	// else if (ft_strlen(pgm->argv[0]) == 4 && !ft_strncmp(pgm->argv[0], "echo", 4))
	// 	ms_echo(pgm);
	// else if (ft_strlen(pgm->argv[0]) == 3 && !ft_strncmp(pgm->argv[0], "env", 3))
	// 	ms_env(pgm);
	// else if (ft_strlen(pgm->argv[0]) == 6 && !ft_strncmp(pgm->argv[0], "export", 6))
	// 	ms_export(pgm);
	// else if (ft_strlen(pgm->argv[0]) == 5 && !ft_strncmp(pgm->argv[0], "unset", 5))
	// 	ms_unset(pgm);
	// else if (ft_strlen(pgm->argv[0]) == 4 && !ft_strncmp(pgm->argv[0], "exit", 4))
	// 	ms_exit(pgm);
	return ;
}