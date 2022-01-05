/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:59:02 by amorcill          #+#    #+#             */
/*   Updated: 2021/07/14 19:48:12 by amorcill         ###   ########.fr       */
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

static char	*ft_inttostr(int sign, int n, char *ret)
{
	while (n != 0)
	{
		*ret = (n % 10) + '0';
		ret--;
		n = n / 10;
	}
	ret++;
	if (sign == 0)
	{
		ret--;
		*ret = '-';
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		nlen;

	if (n == 0 || n == -0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	nlen = ft_intlen(n);
	ret = (char *)malloc((char)nlen + 1);
	if (ret == 0)
		return (0);
	ft_bzero(ret, nlen + 1);
	ret = ret + nlen - 1;
	if (n < 0)
	{
		n = n * (-1);
		ret = ft_inttostr(0, n, ret);
	}
	else
		ret = ft_inttostr(1, n, ret);
	return (ret);
}
