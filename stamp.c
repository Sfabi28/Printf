/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:48:29 by sfabi             #+#    #+#             */
/*   Updated: 2024/04/23 12:08:02 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	stamp_char(t_struct *f)
{
	int	leng;
	int	i;

	i = 0;
	leng = 1;
	while (f->minus == 0 && i < f->nbr_width - 1)
	{
		leng += write(1, " ", 1);
		i++;
	}
	write (1, &f->str[0], 1);
	i++;
	if (f->minus == 1)
	{
		while (i < f->nbr_width)
		{
			write(1, " ", 1);
			i++;
			leng++;
		}
	}
	return (leng);
}

int	stamp_str(t_struct *f)
{
	int	leng;
	int	i;

	i = 0;
	leng = 0;
	handle_width_str(f, i, &leng);
	i = -1;
	while (f->str[++i])
	{
		if ((!ft_strncmp(f->str, "(null)", 6)
				&& (f->nbr_precision < 6 && f->dot == 1)))
			break ;
		if (f->dot == 1 && i >= f->nbr_precision)
			break ;
		leng += write(1, &f->str[i], 1);
	}
	if (f->minus == 1)
	{
		i = 1;
		while (i <= f->nbr_width - leng && i++)
			write(1, " ", 1);
		return (leng + i - 1);
	}
	return (leng);
}

int	stamp_ptr(t_struct *f)
{
	int	leng;
	int	i;

	i = 0;
	leng = 0;
	handle_width_nbr(f, i, &leng);
	if (f->dot == 0 && f->minus == 0 && f->nbr_precision != 0)
		while (i < f->nbr_precision - ft_strlen(f->str) && ++i)
			leng += write(1, " ", 1);
	while (f->str[i])
		leng += write(1, &f->str[i++], 1);
	handle_minus(f, &i, &leng);
	return (leng);
}

int	stamp_int(t_struct *f)
{
	int	leng;
	int	i;
	int	len;

	i = 0;
	leng = 0;
	len = uint_countlen(ft_atoi(f->str));
	if (f->space == 1 && f->str[0] != '-' && ++leng)
		write(1, " ", 1);
	if (f->plus == 1)
		leng += handle_plus(f, &i, len);
	handle_width_nbr(f, i, &leng);
	if (f->str[0] == '-' && (!f->zero || f->dot) && ++i)
		leng += write(1, "-", 1);
	if (f->dot == 1 || f->zero == 1)
		while (++i && i <= f->nbr_precision - len
			+ (f->dot && f->str[0] == '-'))
			leng += write(1, "0", 1);
	i = (f->str[0] == '-') - 1;
	while (f->str[++i])
		if (!(f->str[0] == '0' && f->nbr_precision == 0 && f->dot == 1))
			leng += write(1, &f->str[i], 1);
	handle_minus(f, &i, &leng);
	return (leng);
}

int	stamp_uint(t_struct *f)
{
	int	leng;
	int	i;
	int	len;

	i = 0;
	leng = 0;
	len = uint_countlen(ft_atoi(f->str));
	handle_width_nbr(f, i, &leng);
	if (f->zero == 1 || f->dot == 1)
	{
		while (++i && i <= f->nbr_precision - len
			+ (f->nbr_precision > len && f->dot == 1 && f->str[0] == '-'))
			leng += write(1, "0", 1);
		i = (f->str[0] == '-');
	}
	i = -1;
	while (f->str[++i])
		if (!(f->str[0] == '0' && f->nbr_precision == 0 && f->dot == 1))
			leng += write(1, &f->str[i], 1);
	handle_minus(f, &i, &leng);
	return (leng);
}
