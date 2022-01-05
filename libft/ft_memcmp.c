/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:52:18 by x250              #+#    #+#             */
/*   Updated: 2021/07/08 18:21:05 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*ps1;
	unsigned const char	*ps2;

	if (s1 == NULL && s2 == NULL)
		return (0);
	ps1 = (unsigned const char *)s1;
	ps2 = (unsigned const char *)s2;
	while (n > 0 && *ps1 == *ps2)
	{
		ps1++;
		ps2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((*ps1) - (*ps2));
}
