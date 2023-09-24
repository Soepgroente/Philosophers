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
	henk->alive = true;
	henk->f1 = false;
	henk->f2 = false;
	henk->saturated = false;
	henk->data = data;
}

static void	norm_splitting(t_philo *henk, t_fork *forks, int i)
{
	if (i % 2 == 0)
	{
		henk[i].fork1 = &forks[i - 1];
		henk[i].fork2 = &forks[i];
	}
	else
	{
		henk[i].fork1 = &forks[i];
		henk[i].fork2 = &forks[i - 1];
	}
}

static int	init_philos(t_data *data, t_fork *forks)
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
		if (pthread_mutex_init(&henk[i].lock, NULL) != 0)
			return (-1);
		norm_splitting(henk, forks, i);
		i++;
	}
	henk[0].fork1 = &forks[i - 1];
	return (0);
}

static int	init_mutex_s(t_data *data)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(data->ph_num * sizeof(t_fork));
	if (forks == NULL)
		return (-1);
	data->forks = forks;
	while (i < data->ph_num)
	{
		forks[i].fork = AVAILABLE;
		if (pthread_mutex_init(&forks[i].lock, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (-1);
	return (0);
}

int	init_structs(t_data *data)
{
	data->start_time = get_time();
	if (init_mutex_s(data) == -1)
		return (-1);
	if (init_philos(data, data->forks) == -1)
		return (-1);
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (-1);
	return (0);
}
