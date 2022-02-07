/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 20:52:51 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/07 17:07:12 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	index;
	size_t	i;
	char	*strjoin;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);		
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strjoin = malloc(len1 + len2 + 1);
	if (!strjoin)
		return (0);
	index = 0;
	while (s1[index] != '\0')
	{
		strjoin[index] = s1[index];
		index++;
	}
	i = 0;
	while (s2[i] != '\0')
		strjoin[index++] = s2[i++];
	strjoin[index] = '\0';
	return (strjoin);
}
