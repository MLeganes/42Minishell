/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 10:09:37 by amorcill          #+#    #+#             */
/*   Updated: 2021/11/25 13:52:20 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

static int	ft_vsprintf(char *fmt, va_list args)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] != '%')
		{
			ret += write(1, &fmt[i], 1);
		}
		else
		{
			i++;
			if (ft_check_type(fmt[i]))
				ret += ft_printf_arg(args, fmt[i]);
		}
		i++;
	}
	return (ret);
}

int	ft_printf(const char *fmt, ...)
{
	int		ret;
	va_list	args;

	ret = 0;
	va_start(args, fmt);
	ret = ft_vsprintf((char *)fmt, args);
	va_end(args);
	return (ret);
}
