/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 10:09:16 by amorcill          #+#    #+#             */
/*   Updated: 2022/02/16 11:47:48 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex(unsigned long n, int lower, int reset)
{
	char			hex;
	static int		len;

	if (reset)
		len = 2;
	if (n / 16)
		ft_puthex((n / 16), lower, 0);
	if ((n % 16) > 9)
		hex = 'A' + ((n % 16) - 10);
	else
		hex = ((n % 16) + 48);
	if (lower == 1)
		hex = ft_tolower(hex);
	len += write(1, &hex, 1);
	return (len);
}

int	ft_printf_p(unsigned long ptr)
{
	if (ptr == 0)
		return (write(1, "0x0", 3));
	write(1, "0x", 2);
	return (ft_puthex(ptr, 1, 1));
}
