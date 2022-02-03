/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:22:34 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/01 23:05:09 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir *new_redirection(t_info *ms, int is_app, int is_out)
{
	t_redir *new;
	
	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL); // Exit cleaning everything
	new->type = ms->tmp_tkn->type;
	if (ms->tmp_tkn->next && ms->tmp_tkn->next->data)
		new->file = ms->tmp_tkn->next->data; // Next token contain the file.
	else
		printf("Error: Incomplete command, no file.\n");
	new->is_app = is_app;
	new->is_out = is_out;
	new->next = NULL;
	return (new);
}

void ms_redir_lstadd_last(t_program **pgm, t_redir *new)
{
	t_redir *last;

	if ((*pgm)->redir == NULL)
		(*pgm)->redir = new;
	else
	{
		last = (*pgm)->redir;
		while (last->next)
		{
			last = last->next;
		}
		if ( last)
			last->next = new;
	}
}

void parser_build_redirection(t_info *ms, t_program **pgm)
{
	t_redir *redir;
	
	if (ms->tmp_tkn->type == REDIR_GREAT)
	{
		redir = new_redirection(ms, 0, 1);
		ms_redir_lstadd_last(&(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_DGREAT)
	{
		redir = new_redirection(ms, 1, 1);
		ms_redir_lstadd_last(&(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_LESS)
	{
		redir = new_redirection(ms, 0, 1);
		ms_redir_lstadd_last(&(*pgm), redir);
	}
	else if (ms->tmp_tkn->type == REDIR_DLESS)
		ms_redir_heredoc(ms, &(*pgm));
	//increment to next, that was where file-name is. 
	ms->tmp_tkn = ms->tmp_tkn->next;
}

static int	ms_redir_in(t_redir *tmp, int inb)
{
	int	fd;

	fd = open(tmp->file, O_RDONLY);
	if (fd < 0)
	{
		if (inb == 1)
			printf("Redirection Error \n");	
			//ft_error(1, "No such file or directory\n", inb);
		printf("Redirection Error \n");	
		//ft_error(1, "No such file or directory", inb);
		return (0);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (1);
	}
}

static int	ms_redir_out(t_redir *tmp)
{
	int	fd;

	if (tmp->is_app == 1)
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	redir_selector(t_info *ms, int inb)
{
	t_redir	*tmp;
	int		status;

	tmp = ms->tmp_pgm->redir;
	status = 1;
	while (tmp)
	{
		if (tmp->is_out == 0 && tmp->is_app == 0)
			status = ms_redir_in(tmp, inb);
		else if (tmp->is_out == 1)
			ms_redir_out(tmp);
		else
			printf("Redirection Error \n");	
			//ft_error(127, "Redirection is nonsense", 0);
		tmp = tmp->next;
	}
	return (status);
}