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
				//ft_free_array(paths);
				return (full_path);
			}
			else
			{
				//ft_free_array(paths);
				break ;
			}
		}
		i++;
	}
	return (NULL);
} 
