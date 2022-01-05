/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 10:09:25 by amorcill          #+#    #+#             */
/*   Updated: 2021/11/25 14:08:39 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_s(char *str)
{
	int	ret;

	if (!str)
		return (write(1, "(null)", 6));
	ret = 0;
	ret = ft_strlen(str);
	ret = write(1, str, ret);
	return (ret);
}
