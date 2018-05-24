/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:56:04 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/24 09:02:01 by nmolina          ###   ########.fr       */
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

// static size_t	get_str_len(int n)
// {
// 	size_t		i;

// 	i = 1;
// 	while (n /= 10)
// 		i++;
// 	return (i);
// }

// char			*ft_itoa(int n)
// {
// 	char			*str;
// 	size_t			str_len;
// 	unsigned int	n_cpy;

// 	str_len = get_str_len(n);
// 	n_cpy = n;
// 	if (n < 0)
// 	{
// 		n_cpy = -n;
// 		str_len++;
// 	}
// 	if (!(str = ft_strnew(str_len)))
// 		return (NULL);
// 	str[--str_len] = n_cpy % 10 + '0';
// 	while (n_cpy /= 10)
// 		str[--str_len] = n_cpy % 10 + '0';
// 	if (n < 0)
// 		*(str + 0) = '-';
// 	return (str);
// }
