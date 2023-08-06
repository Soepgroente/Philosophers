/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:50:51 by vincent           #+#    #+#             */
/*   Updated: 2023/08/06 17:00:41 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(char num)
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

int	ft_ato_uint(char *num)
{
	int		i;
	long	result;

	i = 0;
	if (check_num(num) == false)
		return (-1);
	while (num[i])
	{
		result *= 10;
		result += num[i] - '0';
	}
	return ((int) result);
}