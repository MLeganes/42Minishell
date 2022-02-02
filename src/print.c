/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:45:24 by arohmann          #+#    #+#             */
/*   Updated: 2022/02/02 17:28:04 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*print_type(t_type a)
{
	if (a == REDIR_DLESS)
		return ("REDIR_DLESS");
	else if (a == REDIR_LESS)
		return ("REDIR_LESS");
	else if (a == REDIR_DGREAT)
		return ("REDIR_DGREAT");
	else if (a == REDIR_GREAT)
		return ("REDIR_GREAT");
	else if (a == PIPE)
		return ("PIPE");
	else if (a == AMPERSAND)
		return ("AMPERSAND");
	else if (a == IN_DQUOTE)
		return ("IN_DQUOTE");
	else if (a == IN_QUOTE)
		return ("IN_QUOTE");
	else
		return ("TOKEN");
}

void	print_qoutes(t_info *ms)
{
	int		i;
	t_token	*token;

	token = ms->list;
	i = 0;
	while (token != NULL)
	{
		printf(GREEN"%d: "RE, i);
		printf("%-15s", token->data);
		token = token->next;
		i++;
	}
	printf("\n");
	token = ms->list;
	i = 0;
	while (token != NULL)
	{
		printf(RED"%d: "RE, i);
		printf("%-15s", print_type(token->type));
		token = token->next;
		i++;
	}
	printf("\n");
}

void	print_lexer(t_info *ms)
{
	int		i;
	t_token	*token;

	token = ms->list;
	i = 0;
	while (token->next != NULL)
	{
		printf(GREEN"%d: "RE, i);
		printf("%-15s", token->data);
		if (token->next != NULL)
			token = token->next;
		i++;
	}
	printf(GREEN"%d: "RE, i);
	printf("%-15s", token->data);
	printf("\n");
	token = ms->list;
	i = 0;
	while (token->next != NULL)
	{
		printf(RED"%d: "RE, i);
		printf("%-15s", print_type(token->type));
		if (token->next != NULL)
			token = token->next;
		i++;
	}
	printf(RED"%d: "RE, i);
	printf("%-15s", print_type(token->type));
	printf("\n");
}

void	print_env(t_info *ms)
{
	int		i;
	t_env	*token;

	token = ms->env_v;
	i = 0;
	while (token != NULL)
	{
		printf(GREEN"%d: "RE, i);
		printf("%-15s\t", token->var);
		printf("%s", token->content);
		printf("\n");
		token = token->next;
		i++;
	}
}