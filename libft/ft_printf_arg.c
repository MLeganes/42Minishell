/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 10:08:43 by amorcill          #+#    #+#             */
/*   Updated: 2021/11/25 13:51:56 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_arg(va_list args, char fmt)
{
	char	c;

	if (fmt == 'c')
	{
		c = (char)va_arg(args, int);
		return (write(1, &c, 1));
	}
	if (fmt == 's')
		return (ft_printf_s(va_arg(args, char *)));
	if (fmt == 'p')
		return (ft_printf_p((unsigned long)va_arg(args, void *)));
	if (fmt == 'd' || fmt == 'i')
		return (ft_printf_d(va_arg(args, int)));
	if (fmt == 'x')
		return (ft_printf_hex(va_arg(args, unsigned int), 1));
	if (fmt == 'X')
		return (ft_printf_hex(va_arg(args, unsigned int), 0));
	if (fmt == 'u')
		return (ft_printf_u(va_arg(args, unsigned int)));
	if (fmt == '%')
		return (write(1, &"%", 1));
	return (0);
}
