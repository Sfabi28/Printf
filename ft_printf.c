/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:12:58 by sfabi             #+#    #+#             */
/*   Updated: 2024/04/23 13:32:23 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	stamp_hex(t_struct *f, char type)
{
	int		i;
	int		leng;
	int		len;

	i = 0;
	leng = 0;
	if (f->hashtag == 1 && f->str[0] != '0' && type == 'x')
		leng += write(1, "0x", 2);
	else if (f->hashtag == 1 && f->str[0] != '0' && type == 'X')
		leng += write(1, "0X", 2);
	len = ft_strlen(f->str);
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

static	void	count_elements(char *stamp, int *i, t_struct *f)
{
	int		flag;

	flag = 0;
	while (stamp[*i] && (stamp[*i] == '-' || stamp[*i] == '0'
			|| stamp[*i] == '+' || stamp[*i] == ' ' || stamp[*i] == '#'
			|| stamp[*i] == '.' || (stamp[*i] > '0' && stamp[*i] <= '9')))
	{
		if (stamp[*i] == '-')
			f->minus = 1;
		else if (stamp[*i] == '0')
			f->zero = 1;
		else if (stamp[*i] == '+' && ++flag)
			f->plus = 1;
		else if (stamp[*i] == ' ')
			f->space = 1;
		else if (stamp[*i] == '#' && ++flag)
			f->hashtag = 1;
		else if (stamp[*i] == '.' && ++flag)
			f->dot = 1;
		else if (stamp[*i] >= '0' && stamp[*i] <= '9')
			handle_nbr(stamp, i, f, flag);
		(*i)++;
	}
}

static	int	printaction(char type, t_struct *f)
{
	int	leng;

	leng = 0;
	if (type == 'c')
		leng = stamp_char(f);
	else if (type == 's')
		leng = stamp_str(f);
	else if (type == 'p')
		leng = stamp_ptr(f);
	else if (type == 'd' || type == 'i')
		leng = stamp_int(f);
	else if (type == 'u')
		leng = stamp_uint(f);
	else if (type == 'x' || type == 'X')
		leng = stamp_hex(f, type);
	else if (type == '%')
		leng = write(1, "%%", 1);
	return (leng);
}

int	ft_printf(const char *stamp, ...)
{
	va_list		args;
	t_struct	f;
	int			i;
	int			leng;

	leng = 0;
	i = -1;
	va_start(args, stamp);
	set_f(&f);
	while (stamp[++i])
	{
		if (stamp[i] != '%')
			leng += write(1, &stamp[i], 1);
		else if (++i)
		{
			count_elements((char *)stamp, &i, &f);
			set_str(stamp[i], &f, args);
			leng += printaction(stamp[i], &f);
			if (f.str)
				free(f.str);
			set_f(&f);
		}
	}
	va_end(args);
	return (leng);
}
