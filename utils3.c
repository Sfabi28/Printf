/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:48:40 by sfabi             #+#    #+#             */
/*   Updated: 2024/04/23 13:26:08 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_nbr(char *stamp, int *i, t_struct *f, int flag)
{
	if (flag != 0)
		f->nbr_precision = ft_atoi(&stamp[*i]);
	else
		f->nbr_width = ft_atoi(&stamp[*i]);
	while (stamp[*i] >= '0' && stamp[*i] <= '9')
		(*i)++;
	(*i)--;
}

void	handle_minus(t_struct *f, int *i, int *leng)
{
	if (f->minus == 1)
	{
		(*i) = 1;
		while ((*i) <= f->nbr_width - (*leng) && (*i)++)
			write(1, " ", 1);
		(*leng) += (*i) - 1;
	}
}

void	handle_width_str(t_struct *f, int i, int *leng)
{
	int		len;

	if (!ft_strncmp(f->str, "(null)", 6) && f->nbr_precision < 6 && f->dot == 1)
		len = -6;
	else
	{
		len = f->nbr_precision - ft_strlen(f->str);
		if (len < 0 && f->dot == 1)
			len = 0;
	}
	if (f->minus == 0)
	{
		i = 0;
		if (ft_strncmp(f->str, "(null)", 6))
			while (i < ((f->nbr_width - f->nbr_precision) + len) && ++i)
				(*leng) += write(1, " ", 1);
		else
		{
			len = 0;
			if (f->nbr_precision < 6 && f->dot == 1)
				len = -6;
			while (i < f->nbr_width - 6 - len && ++i)
				(*leng) += write(1, " ", 1);
		}
	}
}

void	handle_width_nbr(t_struct *f, int i, int *leng)
{
	int		len;

	len = f->nbr_width - f->nbr_precision;
	if (ft_strlen(f->str) > f->nbr_precision)
		len = f->nbr_width - ft_strlen(f->str)
			+ (f->str[0] == '-' && f->nbr_precision)
			+ (f->str[0] == '0' && f->dot == 1 && f->nbr_precision == 0);
	if (len < 0 && f->dot == 1)
		len = 0;
	if (f->str[0] == '-' && f->nbr_precision)
		len--;
	if (f->minus == 0)
	{
		i = 0;
		if (f->zero && !f->dot && f->str[0] == '-')
			(*leng) += write(1, "-", 1);
		while (i < len && ++i)
		{
			if (f->zero == 1 && f->dot == 0)
				write(1, "0", 1);
			else
				write(1, " ", 1);
		}
		(*leng) += i;
	}
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
