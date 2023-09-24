/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:14:57 by vvan-der          #+#    #+#             */
/*   Updated: 2023/09/23 11:14:13 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	henk_data(t_data *data, t_philo *henk, int num)
{
	henk->num = num;
	henk->num_eaten = 0;
	henk->last_eaten = 0;
	henk->max_eat = data->num_eat;
	henk->t_eat = data->t_eat;
	henk->t_die = data->t_die;
	henk->start_time = data->start_time;
	henk->alive = true;
	henk->saturated = false;
	henk->data = data;
	henk->forks = data->forks;
}

static int	init_philos(t_data *data)
{
	int		i;
	t_philo	*henk;

	i = 0;
	henk = malloc(data->ph_num * sizeof(t_philo));
	if (henk == NULL)
		return (-1);
	data->philos = henk;
	while (i < data->ph_num)
	{
		henk_data(data, &henk[i], i);
		i++;
	}
	return (0);
}

sem_t	*init_semaphore(t_data *data)
{
	sem_t	*forks;

	forks = sem_open("Forkblocker", O_CREAT, "rw", data->ph_num / 2);
	if (forks == NULL)
		return (NULL);
	return (forks);
}

int	init_structs(t_data *data)
{
	data->forks = init_semaphore(data);
	if (data->forks == NULL)
		return (-1);
	if (init_philos(data) == -1)
		return (-1);
	data->start_time = get_time();
	return (0);
}
