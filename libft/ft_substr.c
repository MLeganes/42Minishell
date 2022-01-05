/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 23:43:50 by x250              #+#    #+#             */
/*   Updated: 2021/07/16 14:05:07 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	counter;

	counter = 0;
	substr = NULL;
	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (s != NULL)
	{
		substr = malloc(sizeof(char) * len + 1);
		if (substr == 0)
			return (NULL);
		while (counter < len && s[start + counter] != '\0')
		{
			substr[counter] = s[start + counter];
			counter++;
		}
		substr[counter] = '\0';
	}
	return (substr);
}
