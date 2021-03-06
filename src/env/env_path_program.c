/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path_program.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:09:53 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/20 21:07:14 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_get_path(char **env, char *command);

static char	*env_getenv(char **env, char *var)
{
	int		i;
	int		len_var;

	i = 0;
	len_var = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(var, env[i], len_var) == 0)
		{
			return (env[i]);
		}
		i++;
	}
	return (NULL);
}

/* Used in exec-child to get the right path or not*/
static char	*ms_get_valid_path(char **paths, char *cmd)
{
	int			i;
	char		*command;
	char		*full_path;
	struct stat	ss;

	command = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			g_exit_status = 127;
		full_path = ft_strjoin(paths[i], command);
		if (stat(full_path, &ss) == EXIT_SUCCESS)
		{
			free_str(command);
			return (full_path);
		}
		free_str(full_path);
		i++;
	}
	free_str(command);
	return (NULL);
}

/*
 * @brief	The me_get_path looks for the full path of the command to execute.
 * 
 * @param env Environtment in array.
 * @param command It is the name of the command ex. ls.
 * @return *char The full path to the location of the command. ex. /bin/ls. 
 * NULL is nothing.
 */
static char	*ms_get_path(char **env, char *command)
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

static int	get_path_error(t_info *ms, char *argv)
{
	error_exit_errno(127, argv, "No such file or directory", 0);
	if (ms->tmp_pgm->argv[0] != NULL)
	{
		free(ms->tmp_pgm->argv[0]);
		ms->tmp_pgm->argv[0] = NULL;
		return (EXIT_FAILURE);
	}
	return (0);
}

/***
 * 
 *  NEW VERSION
 * 
 ***/
int	env_search_program_path(t_info *ms, char *argv)
{
	char	*path_values;
	char	*tmp;

	if (access(argv, F_OK) == 0)
		return (EXIT_SUCCESS);
	path_values = env_getenv(ms->env, "PATH");
	if (path_values == NULL)
		return (get_path_error(ms, argv));
	else
	{
		tmp = ms_get_path(ms->env, argv);
		if (tmp != NULL)
		{
			if (ms->tmp_pgm->argv[0])
				free(ms->tmp_pgm->argv[0]);
			ms->tmp_pgm->argv[0] = tmp;
			errno = 0;
			return (EXIT_SUCCESS);
		}
	}
	error_exit_errno(127, argv, "Command not found", 0);
	g_exit_status = 127;
	return (EXIT_FAILURE);
}
