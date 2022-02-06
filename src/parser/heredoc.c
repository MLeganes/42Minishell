/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:20:06 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/06 12:15:37 by annarohmnn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// Exit cleaning everything, line 21
static t_redir	*new_redirection_heredoc(char *file, int is_app, int is_out)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL);
	new->type = REDIR_DLESS;
	new->file = file;
	new->is_app = is_app;
	new->is_out = is_out;
	new->next = NULL;
	return (new);
}

static char	*ms_get_tmp_file(void)
{
	char		*file;
	struct stat	buf;
	int			i;

	i = 1;
	while (i < INT_MAX)
	{
		file = ft_strjoin(".tmp", ft_itoa(i));
		if (stat(file, &buf) == -1)
		{
			return (file);
		}
		free(file);
		i++;
	}
	return (NULL);
}

	/* If delimiter has quote, removed to print it!!! line 56*/
static void	ms_heredoc_writeline(t_info *ms, char *line, int fd, char *del)
{
	int		i;
	int		j;
	char	*new;

	if (ft_strchr(del, '"') || ft_strchr(del, '"'))
		write(fd, line, ft_strlen(line));
	else
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$')
			{
				j = ms_expand_get_len(line, i + 1);
				new = ms_expand_get_value(ms, line, i, j);
				write(fd, new, ft_strlen(new));
				i += j;
			}
			else
				write(fd, &line[i], 1);
			i++;
		}
	}
	write(fd, "\n", 1);
	free(line);
}

	/*	man open
		Flags to open file: O_RDWR | O_CREAT
		Permision for O_CREAT 00700 in octal for everybody, party!!! */
	/* Signal INT Ctrl+C call handler to control here-doc line 96*/
void	ms_redir_heredoc(t_info *ms, t_program **pgm)
{
	char	*delim;
	char	*file;
	char	*line;
	int		fd;

	delim = ms->tmp_tkn->next->data;
	file = ms_get_tmp_file();
	fd = open(file, O_RDWR | O_CREAT, 0777);
	if (fd == -1)
		printf("Error: no tmp file for heredoc.\n");
	signal(SIGINT, signalhandler_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
			break ;
		ms_heredoc_writeline(ms, line, fd, delim);
	}
	ms_redir_lstadd_last(&(*pgm), new_redirection_heredoc(file, 0, 0));
}
