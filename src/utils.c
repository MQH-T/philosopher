#include "philo.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-' && ft_isdigit(str[i + 1]) != 1)
		return (0);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	result = result * sign;
	return (result);
}

int	ft_isnbr(const char *str)
{
	int	i;

	i = 0;
	if (str && !str[i])
	{
		while (is_space(str[i]))
			i++;
		if (str[i] == '+')
			i++;
		while (str[i])
		{
			if (ft_isdigit(str[i]) != 1)
			{
				return (0);
			}
			i++;
		}
	}
	return (1);
}