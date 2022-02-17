/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path_program.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:09:53 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/02/17 23:53:39 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (cmd[0] == '/' && (stat(cmd, &ss) == EXIT_SUCCESS))
			return (cmd);
		full_path = ft_strjoin(paths[i], command);
		if (stat(full_path, &ss) == EXIT_SUCCESS)
		{
			if (command)
				free(command);
			return (full_path);
		}
		if (full_path)
			free(full_path);
		i++;
	}
	if (command)
		free(command);
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

static int 	env_search_no_slash(t_info *ms, char **env, char *argv)
{
	char	*ret;

	if (env_getenv(env, "PATH") != NULL)
	{
		ret = ms_get_path(env, argv);
		if (ret == NULL)
			return (error_exit_status127(argv));
		else
		{
			if (ms->tmp_pgm->argv[0])
				free(ms->tmp_pgm->argv[0]);
			ms->tmp_pgm->argv[0] = ret;
			g_exit_status = EXIT_SUCCESS;
			return (SUCCESS);
		}
	}
	else
		return (error_exit_status127(argv));
}

int	env_search_program_path(t_info *ms, char **env, char *argv)
{
	if ((ft_strchr(argv, '/') == NULL))
		return (env_search_no_slash(ms, env, argv));
	else
	{
		if (access(argv, F_OK) == 0)
		{		
			g_exit_status = EXIT_SUCCESS;
			return (SUCCESS);
		}
		else
			return (error_exit_status127(argv));
	}
}
