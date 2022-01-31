/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:20:06 by amorcill          #+#    #+#             */
/*   Updated: 2022/01/31 18:28:29 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir *new_redirection_heredoc(char *file, int is_app, int is_out)
{
	t_redir *new;
	
	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL); // Exit cleaning everything
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

static void	ms_heredoc_writeline(t_info *ms, char *line, int fd, char *del)
{
	int		i;
	int		j;
	char	*new;

	/* If delimiter has qoute, removed to print it!!! */
	if (ft_strchr(del, '"') || ft_strchr(del, '"'))
		write(fd, line, ft_strlen(line));
	else
	{
		i = 0;
		while (line[i])
		{
			/* Maybe no need to do this in the here-doc*/
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

void	ms_redir_heredoc(t_info *ms, t_program **pgm)
{
	char	*delim;
	char 	*file;
	char 	*line;
	int 	fd;
	
	delim = ms->tmp_tkn->next->data; // Next token contain the delimiter.
	file = ms_get_tmp_file();
	/*	man open
		Flags to open file: O_RDWR | O_CREAT
		Permision for O_CREAT 00700 in octal for everybody, party!!! */
	fd = open(file, O_RDWR | O_CREAT, 0777);
	if (fd == -1)
		printf("Error: no tmp file for heredoc.\n");	
	while (1)
	{
		line = readline(">");
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
			break ;
		ms_heredoc_writeline(ms, line, fd, delim);
		//process_herestring(line, fd, delim);
	}
	ms_redir_lstadd_last(&(*pgm), new_redirection_heredoc(file, 0, 0));
}
