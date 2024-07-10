/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:56:48 by sfabi             #+#    #+#             */
/*   Updated: 2024/04/16 11:45:47 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(char *s)
{
	char	*arr;
	size_t	cont;
	size_t	grandezza;

	cont = 0;
	grandezza = 0;
	while (s[grandezza])
		grandezza++;
	arr = malloc (sizeof (char) * grandezza + 1);
	if (arr == NULL)
		return (NULL);
	while (s[cont])
	{
		arr[cont] = s[cont];
		cont++;
	}
	arr[cont] = '\0';
	return ((char *)(arr));
}

char	*write_char(int c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c + 0;
	str[1] = '\0';
	return (str);
}

char	*write_str(char *str)
{
	char	*str2;

	str2 = NULL;
	if (str)
		str2 = ft_strdup(str);
	if (!str)
		str2 = ft_strdup("(null)");
	if (!str2)
		return (NULL);
	return (str2);
}

int	ft_strlen(char *str)
{
	int	cont;

	cont = 0;
	while (str[cont])
		cont++;
	return (cont);
}

int	handle_plus(t_struct *f, int *i, int len)
{
	int		leng;

	leng = 0;
	len++;
	while (*i < f->nbr_precision - len && ++(*i))
		leng += write(1, " ", 1);
	if (f->str[0] != '-')
		leng += write(1, "+", 1);
	(*i) = 0;
	return (leng);
}
