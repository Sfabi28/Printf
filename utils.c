/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:36:30 by sfabi             #+#    #+#             */
/*   Updated: 2024/04/19 11:50:19 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_f(t_struct *f)
{
	f->dot = 0;
	f->hashtag = 0;
	f->space = 0;
	f->minus = 0;
	f->plus = 0;
	f->zero = 0;
	f->nbr_precision = 0;
	f->nbr_width = 0;
	f->str = 0;
}

long long	ft_atoi(char *str)
{
	int				i;
	long long		nbr;
	long long		sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (str[i] == '-' && i++)
		sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

int	hex_countlen(unsigned long long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 16;
		len++;
	}
	return (len);
}

int	uint_countlen(long long n)
{
	unsigned long long	num;
	long int			cont;
	int					len;

	cont = 1;
	len = 0;
	if (n <= 0)
	{
		len++;
		num = n * -1;
	}
	else
		num = n;
	while (num / cont > 0)
	{
		cont = cont * 10;
		len++;
	}
	return (len);
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
