/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:56:04 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/24 19:47:13 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*s;
	long	nbr;
	int		len;

	len = 1;
	n < 0 ? ++len : 0;
	nbr = n < 0 ? -(long)n : n;
	while (nbr > 9)
	{
		nbr /= 10;
		++len;
	}
	s = (char*)malloc(sizeof(char) * (len + 1));
	s[len] = '\0';
	n < 0 ? *s = '-' : 0;
	nbr = n < 0 ? -(long)n : n;
	while (nbr > 9)
	{
		s[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	s[--len] = nbr + '0';
	return (s);
}
