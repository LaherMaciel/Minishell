/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwencesl <laherwpayotmaciel@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 06:01:16 by lwencesl          #+#    #+#             */
/*   Updated: 2023/01/03 17:08:27 by lwencesl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* 
int	ft_fdputchr(int fd, char s)
{
	return (write(fd, &s, 1));
}

int	ft_fdputstr(int fd, char *s)
{
	size_t	i;

	if (!s)
		return (write(fd, "(null)", 6));
	i = -1;
	while (s[++i] != '\0')
		write(fd, &s[i], 1);
	return (i);
}

int	ft_fdputnbr(int fd, double nbr, char *base, double size)
{
	int	cont;

	cont = 0;
	if (nbr < 0)
	{
		cont += write(fd, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= size)
		cont += ft_fdputnbr(fd, nbr / size, base, size);
	cont += write(fd, &base[((unsigned long)nbr) % ((unsigned long)size)], 1);
	return (cont);
}

int	fdputpoint(int fd, unsigned long long nbr, char *base,
		unsigned long long size)
{
	int	cont;

	cont = 0;
	if (size != 16)
	{
		if (!nbr)
			return (write(fd, "(nil)", 5));
		size = 16;
		write(fd, "0x", 2);
		cont = 2;
	}
	if (nbr >= size)
		cont += fdputpoint(fd, nbr / size, base, size);
	cont += write(fd, &base[(nbr) % (size)], 1);
	return (cont);
}
 */
