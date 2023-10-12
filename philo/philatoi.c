/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philatoi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/06 16:50:51 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/12 15:16:44 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isdigit(char num)
{
	if (num >= 48 && num <= 57)
		return (true);
	else
		return (false);
}

static bool	check_num(char *num)
{
	int	i;

	i = 0;
	while (ft_isdigit(num[i]) == true)
		i++;
	if (num[i] != '\0')
		return (false);
	else
		return (true);
}

int	ft_philatoi(char *num)
{
	int		i;
	int	result;

	i = 0;
	result = 0;
	if (check_num(num) == false)
	{
		printf("Error: invalid input 😕\n");
		return (-1);
	}
	while (num[i])
	{
		result *= 10;
		result += num[i] - '0';
		if (result > INT_MAX)
		{
			printf("Error: atoi overflow\n");
			return (-1);
		}
		i++;
	}
	return ((int) result);
}
