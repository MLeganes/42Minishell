/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 12:33:46 by amorcill          #+#    #+#             */
/*   Updated: 2021/07/16 13:15:41 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if (*(s + len) == (char)c)
		return ((char *)(s + len));
	len--;
	while (len != 0 && *(s + len))
	{
		if (*(s + len) == (char)c)
			return ((char *)(s + len));
		len--;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
