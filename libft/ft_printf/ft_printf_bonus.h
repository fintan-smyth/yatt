/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:45:31 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/08 20:05:29 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_format
{
	int		field_width;
	int		precision;
	int		l_adj;
	int		zero_pad;
	int		alt;
	int		pos_pad;
	int		type;
	char	pos_char;
	char	hex_char;
}	t_format;

enum
{
	e_str = 0,
	e_int = 1,
	e_unsigned = 2,
	e_hex = 3,
	e_ptr = 4,
	e_char = 5,
	e_pcnt = 6
};

void	ft_strrev(char *str);
int		ft_max(int a, int b);
char	*ft_strndup(const char *str, size_t n);
char	*ft_join_or_start(char *s1, char *s2);
void	pad_str_right(char *buf, int width, char c);
void	pad_str_left(char *buf, int width, char c);
char	*put_int_format(int num, t_format fmt);
char	*put_unsigned_format(unsigned int num, t_format fmt);
char	*put_hex_format(int num, t_format fmt);
char	*put_str_format(char *s, t_format fmt);
char	*put_ptr_format(void	*ptr, t_format fmt);
char	*put_char_format(unsigned char c, t_format fmt);
void	clear_t_format(t_format *fmt);
int		parse_format_string(char *str, t_format *fmt, char *conv_chars);
int		extract_til_conv(const char **format, char **line);
int		extract_format(const char **str, t_format *fmt);
char	get_hex_digit(int n, int upper);
void	set_pos_fmt(char poschar, t_format *fmt);
void	print_t_format(t_format fmt);
int		ft_printf(const char *format, ...);

#endif
