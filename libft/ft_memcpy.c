/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x250 <x250@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:56:41 by amorcill          #+#    #+#             */
/*   Updated: 2021/07/06 16:56:39 by x250             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			len;
	unsigned char	*pd;
	unsigned char	*ps;

	if (!dst && !src)
		return (NULL);
	pd = (unsigned char *)dst;
	ps = (unsigned char *)src;
	len = 0;
	while (len < n)
	{
		pd[len] = ps[len];
		len++;
	}
	return (dst);
}
