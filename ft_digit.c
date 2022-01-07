/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:59:49 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/07 04:16:23 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_skip(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long int	ret;

	i = ft_skip(str);
	ret = 0;
	sign = 1;
	if (str[i] == '-')
		ret = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		ret += str[i] - '0';
		if (ft_isdigit(str[i + 1]))
			ret *= 10;
		i++;
		if (ret < 0)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
	}
	return ((int)(ret * sign));
}

void	ft_putnbr(size_t n)
{
	char		c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}
