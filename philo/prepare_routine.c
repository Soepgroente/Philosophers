/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_routine.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 12:22:39 by vincent       #+#    #+#                 */
/*   Updated: 2023/11/02 13:50:27 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_data *data, pthread_t *threads, int i)
{
	if (i != data->ph_num)
		pthread_mutex_unlock(&data->start);
	while (i > 0)
	{
		i--;
		if (pthread_join(threads[i], NULL) != 0)
			return (-1);
	}
	return (0);
}

int	thread_carefully(t_data *data, t_philo *henks)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = data->threads;
	pthread_mutex_lock(&data->start);
	while (i < data->ph_num)
	{
		if (pthread_create(&threads[i], NULL, &henk_is_born, &henks[i]) != 0)
			return (join_threads(data, threads, i), -1);
		i++;
	}
	data->t_start = get_time();
	while (i > 0)
	{
		i--;
		henks[i].last_eaten = data->t_start;
	}
	data->go = true;
	pthread_mutex_unlock(&data->start);
	stalk_philos(data);
	if (join_threads(data, threads, data->ph_num) == -1)
		return (-1);
	return (0);
}
