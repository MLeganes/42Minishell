/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:40:21 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/24 12:08:02 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***
 * 
 * Func. to check if the command path exist e.g. /bin/ls
 * 
 * 
 ***/
static int	ms_existpath(char *file)
{
	int	fd;
	int	ret;

	fd = 0;
	ret = 0;
	fd = open(file, O_RDONLY);
	if (fd > 0)
		ret = 1;
	close(fd);

	/* another way*/
	ret = access(file, F_OK);
	ret = access(file, W_OK);
	return (ret);
}

/***
 * 
 * This func. is not working.
 * I put the func.	get_env_path(t_info *ms) 
 * 
 * 
 ***/
int get_env_pgmpath(t_info *ms, char *pgmname)
{
	(void)ms;
	int i;
	char **path_argv;
	char *path;
	int		ret;

	ret = 0;
	path = getenv("PATH");
	if ( path == NULL)
		path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	
	path_argv = ft_split(path, ':');
	i = 0;
	if ( path_argv[i] != NULL)
	{
		while (path_argv[i])
		{
			printf("this is new path: %s \n", path_argv[i]);
			ft_strlcat(path_argv[i], "/", (ft_strlen(path_argv[i]) + 2));
			ft_strlcat(path_argv[i], pgmname, (ft_strlen(path_argv[i]) + ft_strlen(pgmname) + 1));
			printf(" path: %s \n", path_argv[i]);
			
			if (ms_existpath(path_argv[i]))
			{
				//EXIT
				// BREAK
				if (ms->tmp_pgm->homedir != NULL)
					free(ms->tmp_pgm->homedir);
				ms->tmp_pgm->homedir = ft_strdup(path_argv[i]);
				ret = 1;
				break ;
			}
			i++;
		}
		if (path)
			//free(path);
		path = ft_strjoin("/usr/bin", pgmname);
		if (ms_existpath(path))
		{
			ret = 1;
			ms->tmp_pgm->homedir = path;
		}
	}
	//free_path_argv(path_argv);
	return (ret);
}

/***
 * 
 * Hardcode paths, fast solution to keep coding!!!
 * 
 * 
 ***/
int	get_env_path(t_info *ms)
{	
	ms->tmp_pgm->homedir = ft_strjoin("/bin/", ms->tmp_pgm->argv[0]);
	if (ms_existpath(ms->tmp_pgm->homedir))
		return 1;
	//free(ms->tmp_pgm->homedir);
	ms->tmp_pgm->homedir = ft_strjoin("/usr/bin/", ms->tmp_pgm->argv[0]);
	if (ms_existpath(ms->tmp_pgm->homedir))
		return 1;
	//free(ms->tmp_pgm->homedir);
	ms->tmp_pgm->homedir = ft_strjoin("/usr/sbin/", ms->tmp_pgm->argv[0]);
	if (ms_existpath(ms->tmp_pgm->homedir))
		return 1;
	//free(ms->tmp_pgm->homedir);
	ms->tmp_pgm->homedir = ft_strjoin("/usr/local/bin", ms->tmp_pgm->argv[0]);
	if (ms_existpath(ms->tmp_pgm->homedir))
		return 1;
	//free(ms->tmp_pgm->homedir);
	ms->tmp_pgm->homedir = ft_strjoin("/sbin", ms->tmp_pgm->argv[0]);
	if (ms_existpath(ms->tmp_pgm->homedir))
		return 1;
	//free(ms->tmp_pgm->homedir);
	ms->tmp_pgm->homedir = ft_strjoin("/usr/local/munki", ms->tmp_pgm->argv[0]);
	if (ms_existpath(ms->tmp_pgm->homedir))
		return 1;
	return (0);
}
