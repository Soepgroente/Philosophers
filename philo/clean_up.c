/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/06 18:46:58 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_henks(t_philo *henks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&henks[i].life_lock);
		pthread_mutex_destroy(&henks[i].food_lock);
		i++;
	}
	free(henks);
	henks = NULL;
}

static void	free_forks(t_fork *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&forks[i].lock);
		i++;
	}
	free(forks);
	forks = NULL;
}

void	clean_up(t_data *data)
{
	if (data->forks != NULL)
	{
		free_forks(data->forks, data->ph_num);
		data->forks = NULL;
	}
	if (data->philos != NULL)
	{
		free_henks(data->philos, data->ph_num);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->print_lock);
	if (data->threads != NULL)
		free(data->threads);
}
