/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:48:36 by vincent           #+#    #+#             */
/*   Updated: 2023/09/17 14:55:26 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_forks(t_data *data, bool *forks)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		if (forks[i] == false)
			printf("[%d] available\n", i);
		else
			printf("[%d] taken\n", i);
		i++;
	}
}