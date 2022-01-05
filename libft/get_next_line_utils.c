/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:53:36 by amorcill          #+#    #+#             */
/*   Updated: 2021/10/01 15:49:08 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_find_index(const char *s, int c)
{
	int	index;

	index = 0;
	if (s != NULL)
	{
		while (s[index] != '\0')
		{
			if (s[index] == (char)c)
				return (index);
			index++;
		}
		if (s[index] == (char)c)
			return (index);
	}
	return (-1);
}

char	*gnl_strdup(const char *s)
{
	int		len;
	int		count;
	char	*ret;

	count = 0;
	len = gnl_strlen(s);
	ret = (char *)malloc(len + 1);
	if (ret)
	{
		while (count < len)
		{
			ret[count] = s[count];
			count++;
		}
		ret[count] = '\0';
	}
	return (ret);
}

size_t	gnl_strlen(const char *ch)
{
	int	count;

	if (ch == NULL)
		return (0);
	count = 0;
	while (*(ch + count))
	{
		count++;
	}
	return (count);
}

char	*gnl_strjoin(char *s1, char *s2)
{	
	size_t	index;
	size_t	i;
	char	*strjoin;

	strjoin = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!strjoin)
		return (0);
	index = 0;
	if (s1 != NULL)
	{
		while (s1[index] != '\0')
		{
			strjoin[index] = s1[index];
			index++;
		}
		free(s1);
	}
	i = 0;
	while (s2[i] != '\0')
		strjoin[index++] = s2[i++];
	strjoin[index] = '\0';
	return (strjoin);
}

char	*gnl_substr(const char *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	counter;

	counter = 0;
	substr = NULL;
	if (s == NULL)
		return (NULL);
	if (len > gnl_strlen(s + start))
		len = gnl_strlen(s + start);
	if (start > gnl_strlen(s))
		return (gnl_strdup(""));
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
