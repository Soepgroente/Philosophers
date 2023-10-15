/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/15 19:57:54 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_henks(t_philo *henks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&henks[i].lock);
		i++;
	}
	free(henks);
	henks = NULL;
}

void	destroy_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	forks = NULL;
}

void	clean_up(t_data *data)
{
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->start);
	destroy_forks(data->forks, data->ph_num);
	free_henks(data->philos, data->ph_num);
	if (data->threads != NULL)
		free(data->threads);
}
