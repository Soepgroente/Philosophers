/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 11:04:00 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_henks(t_philo *henk, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		sem_close(henk[i].lock);
		i++;
	}
	free(henk);
	henk = NULL;
}

void	clean_up(t_data *data)
{
	if (data->philos != NULL)
	{
		free_henks(data->philos, data->ph_num);
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
}
