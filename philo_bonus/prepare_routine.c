/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_routine.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 12:22:39 by vincent       #+#    #+#                 */
/*   Updated: 2023/09/24 20:11:21 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	run_threads(t_data *data, t_philo *philos)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc((data->ph_num) * sizeof(pthread_t));
	if (threads == NULL)
		return (-1);
	while (i < data->ph_num)
	{
		if (pthread_create(&threads[i], NULL, &start_routine, &philos[i]) != 0)
			return (-1);
		i++;
	}
	// stalk_philos(data);
	i = 0;
	while (i < data->ph_num)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
