/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:27:31 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/16 12:46:16 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_heredoc_tmp_file(void)
{
	char		*file;
	char		*tmp_n;
	struct stat	buf;
	int			i;

	i = 1;
	while (i < INT_MAX)
	{
		tmp_n = ft_itoa(i);
		file = ft_strjoin(".tmp", tmp_n);
		if (tmp_n)
			free(tmp_n);
		if (stat(file, &buf) == -1)
		{
			return (file);
		}
		if (file)
			free(file);
		i++;
	}
	return (NULL);
}

void	ms_redir_heredoc_init(t_heredoc *hd, t_info *ms)
{
	hd->del_qu = 0;
	hd->ret = 1;
	hd->exit = 1;
	hd->fd_stdin = dup(STDIN_FILENO);
	if (ms->tmp_tkn->next->data == NULL)
	{
		error_exit(" heredoc ", "no tmp file for heredoc");
		hd->ret = 0;
	}
	hd->delim = ms->tmp_tkn->next->data;
	hd->del_qu = ms->tmp_tkn->next->in_dq + ms->tmp_tkn->next->in_q;
	hd->file = ms_heredoc_tmp_file();
	hd->fd = open(hd->file, O_RDWR | O_CREAT, 0644);
	if (hd->fd == -1)
	{
		error_exit(" heredoc ", "no tmp file for heredoc");
		hd->ret = 0;
	}
}