/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/30 18:22:49 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_sjonnies(t_philo *sjon, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		sem_close(sjon[i].lock);
		i++;
	}
	free(sjon);
	sjon = NULL;
}

void	clean_up(t_data *data)
{
	if (data->philos != NULL)
	{
		free_sjonnies(data->philos, data->ph_num);
		data->philos = NULL;
	}
	if (data->forks != NULL)
	{
		sem_close(data->forks);
		data->forks = NULL;
	}
	if (data->print != NULL)
	{
		sem_close(data->print);
		data->print = NULL;
	}
	if (data->threads != NULL)
		free(data->threads);
}
