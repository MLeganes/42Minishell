/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:34:56 by amorcill          #+#    #+#             */
/*   Updated: 2021/06/30 16:25:27 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		needlelen;
	const char	*ret;
	const char	*ptrhaystack;
	const char	*ptrneedle;
	int			result;

	result = 1;
	ptrhaystack = haystack;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*ptrhaystack && len != 0)
	{
		needlelen = ft_strlen(needle);
		ret = ptrhaystack;
		ptrneedle = needle;
		if (len >= needlelen)
			result = ft_strncmp(ptrhaystack, ptrneedle, needlelen);
		if (result == 0)
			return ((char *)ret);
		ptrhaystack++;
		len--;
	}
	return (0);
}
