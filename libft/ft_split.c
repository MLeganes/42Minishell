/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:23:56 by x250              #+#    #+#             */
/*   Updated: 2021/07/15 13:25:25 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *str, char c)
{
	int		words;
	int		isword;
	char	*s;

	s = (char *)str;
	words = 0;
	isword = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			isword = 0;
		}
		else if (isword == 0)
		{
			isword = 1;
			words++;
		}
		s++;
	}
	return (words);
}

static void	ft_findwords(char **result, char *s, char c, int slen)
{
	char	*start;
	int		counter;
	int		len;

	start = (char *)s;
	counter = 0;
	len = 0;
	while (len < slen)
	{
		if (*s == c)
		{
			s++;
			len++;
		}
		else if (*s != c)
		{
			start = (char *)s;
			s = ft_strchr(start, c);
			if (s == 0)
				s = start + (slen - len);
			len += s - start;
			result[counter++] = ft_substr(start, 0, s - start);
		}
	}
	result[counter] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;
	char	*set;
	char	*copy;
	int		slen;

	if (s == 0)
		return (0);
	set = &c;
	slen = ft_strlen(s);
	words = ft_countwords(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (result == 0)
		return (0);
	if (words == 1)
	{
		result[0] = ft_strtrim(s, set);
		result[1] = NULL;
		return (result);
	}
	copy = (char *)s;
	ft_findwords(result, copy, c, slen);
	return (result);
}
