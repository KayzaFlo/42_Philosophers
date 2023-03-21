/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:18:40 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/15 16:06:35 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n')
		return (1);
	if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	atoi_overflow(const char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nbr > INT32_MAX / 10 + 1 || nbr < INT32_MIN / 10)
			return (-1);
		if (nbr * 10 > INT32_MAX - (str[i] - '0')
			|| nbr * 10 < -(str[i] - '0'))
			return (-1);
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
