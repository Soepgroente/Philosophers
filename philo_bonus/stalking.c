/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stalking.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/30 17:25:48 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/31 13:44:00 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	simulation_end(t_data *data)
{
	int	i;

	i = 0;
	kill_children(data->processes, data->ph_num);
	while (i < data->ph_num)
	{
		waitpid(data->processes[i], NULL, 0);
		i++;
	}
}

static void	*check_saturation(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->ph_num)
	{
		sem_wait(data->saturated);
		i++;
	}
	return (NULL);
}

int	wait_for_ending(t_data *data)
{
	pthread_t	thread;

	if (data->num_eat < INT_MAX)
	{
		if (pthread_create(&thread, NULL, &check_saturation, data) != 0)
			return (-1);
		pthread_join(thread, NULL);
		return (0);
	}
	sem_wait(data->death);
	return (0);
}
