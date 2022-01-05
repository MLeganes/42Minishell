/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x250 <x250@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 01:11:20 by x250              #+#    #+#             */
/*   Updated: 2021/07/07 10:46:36 by x250             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		count;
	char	*ret;

	count = 0;
	len = ft_strlen(s);
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
