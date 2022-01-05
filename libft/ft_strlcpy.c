/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 23:19:48 by x250              #+#    #+#             */
/*   Updated: 2021/07/02 14:48:30 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{	
	size_t	slen;
	size_t	counter;

	if (dst != NULL && src != NULL)
	{
		slen = ft_strlen(src);
		if (size > 0)
		{
			counter = 0;
			while (counter < (size - 1) && src[counter] != '\0')
			{
				dst[counter] = src[counter];
				counter++;
			}
			dst[counter] = '\0';
		}
		return (slen);
	}
	return (0);
}
