/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_structs.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/09 11:25:55 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	henk_data(t_data *data, t_philo *henk, int num)
{
	henk->num = num;
	henk->num_eaten = 0;
	henk->max_eat = data->num_eat;
	henk->t_eat = data->t_eat;
	henk->t_die = data->t_die;
	if (data->t_sleep == 0 || data->t_eat == 0)
		henk->t_think = 1;
	else
		henk->t_think = 0;
	henk->alive = true;
	henk->saturated = false;
	henk->data = data;
}

static void	fork_assignment(t_philo *henk, t_fork *forks, int i)
{
	henk[i].fork1 = &forks[i];
	henk[i].fork2 = &forks[i + 1];
	if (i + 1 == henk->data->ph_num)
	{
		if (henk->data->ph_num % 2 == 1)
		{
			henk[i].fork1 = &forks[0];
			henk[i].fork2 = &forks[i];
		}
		else
		{
			henk[i].fork1 = &forks[i];
			henk[i].fork2 = &forks[0];
		}
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
		if (pthread_mutex_init(&henk[i].life_lock, NULL) != 0)
			return (-1);
		if (pthread_mutex_init(&henk[i].food_lock, NULL) != 0)
			return (-1);
		fork_assignment(henk, forks, i);
		i++;
	}
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
		if (pthread_mutex_init(&forks[i].lock, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (-1);
	return (0);
}

int	init_structs(t_data *data)
{
	data->threads = malloc(data->ph_num * sizeof(pthread_t));
	if (data->threads == NULL)
		return (-1);
	if (init_mutex_s(data) == -1)
		return (-1);
	if (init_philos(data, data->forks) == -1)
		return (-1);
	return (0);
}
