/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:22:39 by vincent           #+#    #+#             */
/*   Updated: 2023/09/22 13:40:11 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	end_simulation(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	run_threads(t_data *data)
{
	pthread_t	*threads;
	t_philo		*philos;
	int			i;
	
	i = 0;
	philos = data->philos;
	threads = malloc((data->ph_num) * sizeof(pthread_t));
	if (threads == NULL)
		return (-1);
	while (i < data->ph_num)
	{
		pthread_create(&threads[i], NULL, &start_routine, (void *) &philos[i]);
		i++;
	}
	data->start_time = get_time();
	stalk_philos(data);
	end_simulation(data, threads);
	return (0);
}
