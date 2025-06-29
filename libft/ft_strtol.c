/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:37:42 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/13 17:29:25 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_base(char **nptr, int base)
{
	if (base < 0 || base == 1 || base > 36)
		return (-1);
	if (base == 16)
	{
		if (ft_tolower(*((*nptr) + 1)) == 'x')
			*nptr = (*nptr) + 2;
		return (16);
	}
	if (base != 0)
		return (base);
	if (**nptr != '0')
		return (10);
	if (ft_tolower(*((*nptr) + 1)) == 'x')
	{
		*nptr = (*nptr) + 2;
		return (16);
	}
	*nptr = (*nptr) + 1;
	return (8);
}

static long	add_digits_pos(char **nptraddr, char *bstr, int base)
{
	char	*chr;
	char	*nptr;
	long	num;

	num = 0;
	nptr = *nptraddr;
	chr = ft_strchr(bstr, ft_tolower(*nptr));
	while (chr < &bstr[base])
	{
		num *= base;
		num += chr - bstr;
		nptr++;
		if (num < 0)
		{
			num = LONG_MAX;
			errno = ERANGE;
			break ;
		}
		chr = ft_strchr(bstr, ft_tolower(*nptr));
	}
	while (ft_strchr(bstr, ft_tolower(*nptr)) < &bstr[base])
		nptr++;
	*nptraddr = nptr;
	return (num);
}

static long	add_digits_neg(char **nptraddr, char *bstr, int base)
{
	char	*chr;
	char	*nptr;
	long	num;

	num = 0;
	nptr = *nptraddr;
	chr = ft_strchr(bstr, ft_tolower(*nptr));
	while (chr < &bstr[base])
	{
		num *= base;
		num -= chr - bstr;
		nptr++;
		if (num > 0)
		{
			num = LONG_MIN;
			errno = ERANGE;
			break ;
		}
		chr = ft_strchr(bstr, ft_tolower(*nptr));
	}
	while (ft_strchr(bstr, ft_tolower(*nptr)) < &bstr[base])
		nptr++;
	*nptraddr = nptr;
	return (num);
}

static void	handle_ws_sign(char **nptraddr, int *sign)
{
	char	*nptr;

	*sign = 1;
	nptr = *nptraddr;
	while ((*nptr == ' ') || (*nptr <= '\r' && *nptr >= '\t'))
		nptr++;
	if ((*nptr == '+') || (*nptr == '-'))
	{
		if (*nptr == '-')
			*sign = -1;
		nptr++;
	}
	*nptraddr = nptr;
}

long	ft_strtol(char *nptr, char **endptr, int base)
{
	static char	*bstr = "0123456789abcdefghijklmnopqrstuvwxyz";
	long		num;
	int			sign;
	char		*chr;

	if (endptr != NULL)
		*endptr = nptr;
	handle_ws_sign(&nptr, &sign);
	base = get_base(&nptr, base);
	if (base == -1)
	{
		errno = EINVAL;
		return (0);
	}
	chr = ft_strchr(bstr, ft_tolower(*nptr));
	if (chr == NULL)
		return (0);
	if (sign > 0)
		num = add_digits_pos(&nptr, bstr, base);
	else
		num = add_digits_neg(&nptr, bstr, base);
	if (endptr != NULL)
		*endptr = nptr;
	return (num);
}
