/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_routine.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 12:22:39 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/03 16:39:51 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	run_threads(t_data *data, t_philo *philos)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = data->threads;
	data->t_start = get_time();
	while (i < data->ph_num)
	{
		philos[i].t_start = data->t_start;
		philos[i].last_eaten = data->t_start;
		if (pthread_create(&threads[i], NULL, &sjon_is_born, &philos[i]) != 0)
			return (-1);
		i++;
	}
	stalk_philos(data);
	i = 0;
	while (i < data->ph_num)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
