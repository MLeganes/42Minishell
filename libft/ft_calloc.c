/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:56:02 by x250              #+#    #+#             */
/*   Updated: 2021/07/08 18:28:07 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*pointer;

	pointer = malloc((nmemb * size));
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, (nmemb * size));
	return (pointer);
}
