/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philatoi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/06 16:50:51 by vincent       #+#    #+#                 */
/*   Updated: 2023/09/11 15:13:46 by vvan-der      ########   odam.nl         */
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
	long	result;

	i = 0;
	result = 0;
	if (check_num(num) == false)
		return (printf("Error: invalid input\n"), -1);
	while (num[i])
	{
		result *= 10;
		result += num[i] - '0';
		if (result > INT_MAX)
			return (printf("Error: atoi overflow\n"), -1);
		i++;
	}
	return ((int) result);
}
