/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:12:32 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/07 16:55:25 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *ch)
{
	int	count;

	count = 0;
	if (ch == NULL)
		return (0);
	while (*(ch + count))
	{
		count++;
	}
	return (count);
}
