/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x250 <x250@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:25:43 by x250              #+#    #+#             */
/*   Updated: 2021/07/16 22:08:43 by x250             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t buffer)
{
	size_t	counter;
	size_t	s;
	size_t	d;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (buffer != 0)
	{
		counter = 0;
		while (d + counter < (buffer - 1) && src[counter] != '\0')
		{
			dst[d + counter] = src[counter];
			counter++;
		}
		if (d + counter < buffer)
			dst[d + counter] = '\0';
	}
	if (buffer > d)
		return (d + s);
	return (buffer + s);
}
