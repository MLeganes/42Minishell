/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:57:56 by amorcill          #+#    #+#             */
/*   Updated: 2021/07/16 13:20:35 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ret;

	if (s1 == 0)
		return (0);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, (int)s1[start]) && start <= end)
		start++;
	if (s1[start] == '\0')
		return (ft_strdup(""));
	while (ft_strchr(set, (int)s1[end]) && end != 0)
		end--;
	end++;
	ret = ft_substr(s1, (unsigned int)start, (end - start));
	return ((char *)ret);
}
