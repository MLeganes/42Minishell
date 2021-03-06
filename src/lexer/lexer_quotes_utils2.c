/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:54:04 by arohmann          #+#    #+#             */
/*   Updated: 2022/02/20 21:19:05 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_end_tmp(char **tmp, int *i)
{
	(*i) = ft_strlen(*tmp);
	(*tmp)[(*i)] = '\0';
}

char	*ms_error_return(char *tmp, char *str, int *err, int b)
{
	if (b == 1)
		*err = -1;
	free_str(tmp);
	free_str(str);
	return (NULL);
}
