/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:09:53 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/10 10:45:09 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_get_valid_path(char **paths, char *cmd)
{
	int			i;
	char		*command;
	char		*full_path;
	struct stat	stat_buffer;

	command = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		if (cmd[0] == '/' && (stat(cmd, &stat_buffer)== EXIT_SUCCESS))
			return (cmd);
		full_path = ft_strjoin(paths[i], command);
		if (stat(full_path, &stat_buffer) == EXIT_SUCCESS)
		{
			free(command);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(command);
	return (NULL);
}

char	*ms_get_path(char **env, char *command)
{
	int		i;
	char	**paths;
	char	*full_path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			paths = ft_split(&env[i][5], ':');
			full_path = ms_get_valid_path(paths, command);
			if (full_path != NULL)
			{
				free_argv(paths);
				return (full_path);
			}
			else
			{
				free_argv(paths);
				break ;
			}
		}
		i++;
	}
	return (NULL);
}
