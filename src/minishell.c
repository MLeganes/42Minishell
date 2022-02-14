/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:00:24 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/14 16:17:52 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int g_exit_status;

static char	*minishell_gnl_free_line(char *line);
static char	*str_append_chr(char *str, char append);

char	*minishell_get_next_line(int fd)
{
	char	*line;
	char	buffer;
	int		check;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	check = read(fd, &buffer, 1);
	if (check == -1 || check == 0)
		return (minishell_gnl_free_line(line));
	while (check > 0)
	{
		line = str_append_chr(line, buffer);
		if (line == NULL)
			return (NULL);
		if (buffer == '\n')
			return (line);
		check = read(fd, &buffer, 1);
	}
	if (check == -1)
		return (minishell_gnl_free_line(line));
	return (line);
}

static char	*str_append_chr(char *str, char append)
{
	char	*new_str;
	int		i;

	if (str == NULL)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 2);
	if (new_str != NULL)
	{
		i = 0;
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = append;
		new_str[i + 1] = '\0';
	}
	free(str);
	return (new_str);
}

static char	*minishell_gnl_free_line(char *line)
{
	free(line);
	return (NULL);
}

void init_struct(t_info *info)
{
	info->prompt = "\001\033[0;32m\002❯\e[1m_\e[0m \001\033[0m\002";
	info->list = NULL;
	info->cmdline = NULL;
	info->tmp_tkn = NULL;
	info->state = STATE_GENERAL;
	info->idx = 0;
	info->ntok = 0;
	info->npipes = 0;
	info->pgmlist = NULL;
	info->npgms = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;

	(void)argv;
	(void)argc;
	signal(SIGQUIT, SIG_IGN);
	get_env(&info, env);
	info.env = env;
 	while (1)
	{
		init_struct(&info);
		signal(SIGINT, signalhandler_ctrlc);
		if (isatty(STDIN_FILENO))
			info.cmdline = readline(info.prompt);
		else
			info.cmdline = minishell_get_next_line(0);
		if (info.cmdline == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDERR_FILENO, "exit\n", 5);
			free_end(&info);
			exit (g_exit_status);
		}
		signal(SIGINT, SIG_IGN);
		if (lexer(&info) == 0)
		{
			if (parser(&info) != ERROR)
				execute(&info);
		}
		free_after_cmd(&info);
		//system("leaks minishell");
	}	
	//system("leaks minishell");
	free_end(&info);
	return (0);
}
	
