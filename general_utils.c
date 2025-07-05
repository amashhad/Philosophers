/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:55:12 by amashhad          #+#    #+#             */
/*   Updated: 2025/07/05 21:44:05 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_digit(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

int	safe_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	if (!is_digit(str + i))
	{
		fputendl(2, "Error: not a digit");
		return (-1);
	}
	while (str[i])
	{
		result *= 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	chk_val(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (safe_atoi(str[i]) < 0)
		{
			if (!is_digit(str[i]) && str[i][0] == '-')
			{
				fputendl(2, "Error: Values shouldn't be in negatives");
				return (1);
			}
			else
				return (1);
		}
		if (safe_atoi(str[i]) == 0)
		{
			fputendl(2, "Error: Values shouldn't be lower than 1");
			return (1);
		}
		i++;
	}
	return (0);
}

void	*my_calloc(size_t nmem, size_t size)
{
	void	*ptr;

	ptr = malloc(size * nmem);
	if (!ptr)
	{
		fputendl(2, "Error: malloc failure");
		return (NULL);
	}
	memset(ptr, 0, size * nmem);
	return (ptr);
}
