/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:31:27 by sfabi             #+#    #+#             */
/*   Updated: 2024/04/18 14:26:14 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*write_ptr(unsigned long long hex)
{
	char				*str;
	unsigned int		cont;
	unsigned long long	n_cifre;
	char				*strcont;

	if (hex == 0)
		return (ft_strdup("(nil)"));
	str = malloc(sizeof(char) * (hex_countlen(hex) + 3));
	if (!str)
		return (NULL);
	cont = 0;
	n_cifre = 1;
	strcont = "0123456789abcdef";
	while (hex / 16 >= n_cifre)
		n_cifre = n_cifre * 16;
	str[cont++] = '0';
	str[cont++] = 'x';
	while (n_cifre != 0)
	{
		str[cont++] = strcont[hex / n_cifre];
		hex = hex % n_cifre;
		n_cifre = n_cifre / 16;
	}
	str[cont] = '\0';
	return (str);
}

static	char	*write_int(int nbr)
{
	char	*str;
	int		cont;
	int		n_cifre;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	str = malloc(sizeof(char) * (uint_countlen(nbr)) + 1);
	if (!str)
		return (NULL);
	cont = 0;
	n_cifre = 1;
	if (nbr < 0)
		str[cont++] = '-';
	if (nbr < 0)
		nbr = -nbr;
	while (nbr / 10 >= n_cifre)
		n_cifre = n_cifre * 10;
	while (n_cifre != 0)
	{
		str[cont++] = nbr / n_cifre + '0';
		nbr = nbr % n_cifre;
		n_cifre = n_cifre / 10;
	}
	str[cont] = '\0';
	return (str);
}

static	char	*write_und(unsigned int nbr)
{
	char				*str;
	int					cont;
	unsigned long long	n_cifre;

	cont = 0;
	str = malloc(sizeof(char) * (uint_countlen(nbr)) + 1);
	if (!str)
		return (NULL);
	n_cifre = 10;
	while (nbr >= n_cifre)
		n_cifre = n_cifre * 10;
	while (n_cifre > 1)
	{
		n_cifre = n_cifre / 10;
		str[cont++] = nbr / n_cifre + '0';
		nbr = nbr % n_cifre;
	}
	str[cont] = '\0';
	return (str);
}

static	char	*write_hex(unsigned int hex, char stamp)
{
	char				*str;
	unsigned int		cont;
	unsigned long long	n_cifre;
	char				*strcont;

	str = malloc(sizeof(char) * (hex_countlen(hex) + 1));
	if (!str)
		return (NULL);
	cont = 0;
	n_cifre = 16;
	strcont = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while (hex >= n_cifre)
		n_cifre = n_cifre * 16;
	while (n_cifre > 1)
	{
		n_cifre = n_cifre / 16;
		str[cont++] = strcont[hex / n_cifre];
		if (stamp == 'X')
			str[cont - 1] = ft_toupper(str[cont - 1]);
		hex = hex % n_cifre;
	}
	str[cont] = '\0';
	return (str);
}

void	set_str(char type, t_struct *f, va_list args)
{
	if (type == 'c')
		f->str = write_char(va_arg(args, int));
	else if (type == 's')
		f->str = write_str(va_arg(args, char *));
	else if (type == 'p')
		f->str = write_ptr(va_arg(args, unsigned long long));
	else if (type == 'd' || type == 'i')
		f->str = write_int(va_arg(args, int));
	else if (type == 'u')
		f->str = write_und(va_arg(args, unsigned int));
	else if (type == 'x' || type == 'X')
		f->str = write_hex(va_arg(args, unsigned int), type);
}
