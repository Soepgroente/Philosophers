/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:18:26 by vvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 23:30:17 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_henks(t_philo *henk, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&henk[i].lock);
		i++;
	}
	free(henk);
	henk = NULL;
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
}
