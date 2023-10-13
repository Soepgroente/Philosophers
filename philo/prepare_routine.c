/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_routine.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 12:22:39 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/13 15:54:03 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_threads(t_data *data, t_philo *philos)
{
	pthread_t	*t;
	int			i;

	i = 0;
	t = data->threads;
	pthread_mutex_lock(&data->start);
	while (i < data->ph_num)
	{
		if (pthread_create(&t[i], NULL, &henk_is_born, &philos[i]) != 0)
			return (-1);
		philos[i].last_eaten = get_time();
		i++;
	}
	data->t_start = get_time();
	pthread_mutex_unlock(&data->start);
	stalk_philos(data);
	i = 0;
	while (i < data->ph_num)
	{
		if (pthread_join(t[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
