/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:51:21 by amorcill          #+#    #+#             */
/*   Updated: 2021/06/30 12:17:19 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1p;
	unsigned char	*s2p;

	s1p = (unsigned char *)s1;
	s2p = (unsigned char *)s2;
	while (*s1p != '\0' && *s2p != '\0' && *s1p == *s2p && n != 0)
	{
		s1p++;
		s2p++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((*s1p) - (*s2p));
}
