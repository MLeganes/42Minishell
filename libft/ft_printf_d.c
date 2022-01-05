/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 10:09:07 by amorcill          #+#    #+#             */
/*   Updated: 2021/11/25 14:09:17 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int		count;
	int		sign;

	sign = 1;
	if (n < 0)
	{
		sign = 0;
		n = n * -1;
	}
	count = 0;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	if (sign == 0)
		count++;
	return (count);
}

int	ft_printf_d(int d)
{
	if (d == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_putnbr_fd(d, 1);
	return (ft_intlen(d));
}
