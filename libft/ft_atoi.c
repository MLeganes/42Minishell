/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:46:18 by amorcill          #+#    #+#             */
/*   Updated: 2021/07/29 11:40:30 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n'
			|| c == ' '))
		return (1);
	return (0);
}

static int	ft_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned int	result;
	int				sign;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = ft_sign(*str);
		str++;
	}
	while (ft_isdigit(*str) && *str != '\0' && result < 2147483648)
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	if (sign == -1 && result <= 2147483648)
		return (sign * (int)result);
	else if (sign == 1 && result <= 2147483647)
		return ((int)result);
	else if (sign == 1 && result > 2147483647)
		return (-1);
	return (0);
}
