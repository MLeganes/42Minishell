/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annarohmnn <annarohmnn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 20:52:51 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/07 20:33:59 by annarohmnn       ###   ########.fr       */
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

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strjoin = malloc(len1 + len2 + 1);
	if (!strjoin)
		return (0);
	index = 0;
	while (s1 != NULL && s1[index] != '\0')
	{
		strjoin[index] = s1[index];
		index++;
	}
	i = 0;
	while (s2 != NULL && s2[i] != '\0')
		strjoin[index++] = s2[i++];
	strjoin[index] = '\0';
	return (strjoin);
}
