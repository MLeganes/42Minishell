/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 18:31:04 by amorcill          #+#    #+#             */
/*   Updated: 2021/11/25 14:08:51 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(unsigned int n)
{
	int		count;

	count = 0;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}	
	return (count);
}

static void	ft_putuinbr_fd(unsigned int n, int fd)
{
	if (n / 10)
		ft_putuinbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

int	ft_printf_u(unsigned int ui)
{
	int	ret;

	if (ui == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_putuinbr_fd(ui, 1);
	ret = 0;
	ret = ft_intlen(ui);
	return (ret);
}
