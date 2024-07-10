/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:02:05 by sfabi             #+#    #+#             */
/*   Updated: 2024/04/23 13:27:19 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_struct
{
	int		dot;
	int		hashtag;
	int		space;
	int		minus;
	int		plus;
	int		zero;
	int		nbr_precision;
	int		nbr_width;
	char	*str;
}	t_struct;

int				ft_printf(const char *stamp, ...);
void			set_str(char type, t_struct *f, va_list args);
void			set_f(t_struct *f);
void			set_f(t_struct *f);
int				stamp_char(t_struct *f);
int				stamp_str(t_struct *f);
int				stamp_int(t_struct *f);
int				stamp_uint(t_struct *f);
int				stamp_hex(t_struct *f, char type);
int				stamp_ptr(t_struct *f);
long long		ft_atoi(char *str);
int				hex_countlen(unsigned long long num);
int				uint_countlen(long long n);
int				ft_toupper(int c);
char			*write_char(int c);
char			*write_str(char *str);
char			*ft_strdup(char *s);
int				ft_strlen(char *str);
int				handle_plus(t_struct *f, int *i, int len);
void			handle_nbr(char *stamp, int *i, t_struct *f, int flag);
void			handle_minus(t_struct *f, int *i, int *leng);
void			handle_width_str(t_struct *f, int i, int *leng);
void			handle_width_nbr(t_struct *f, int i, int *leng);
int				ft_strncmp(char *s1, char *s2, unsigned int n);

#endif
