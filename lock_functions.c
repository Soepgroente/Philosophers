/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:28:03 by vvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 13:28:54 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_henk(t_philo *henk, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	henk->alive = false;
	pthread_mutex_unlock(lock);
}

bool	check_if_alive(t_philo *henk, pthread_mutex_t *lock)
{
	int	time;

	time = get_runtime(henk->data->start_time, henk);
	pthread_mutex_lock(lock);
	if (henk->alive == false)
		return (false);
	if (henk->t_die < time - henk->last_eaten)
	{
		henk->alive = false;
		pthread_mutex_unlock(lock);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(lock);
		return (true);
	}
}

void	return_forks(t_philo *henk, t_fork *fork1, t_fork *fork2)
{
	pthread_mutex_lock(&fork1->lock);
	fork1->fork = AVAILABLE;
	pthread_mutex_unlock(&fork1->lock);
	henk->f1 = false;
	pthread_mutex_lock(&fork2->lock);
	fork2->fork = AVAILABLE;
	pthread_mutex_unlock(&fork2->lock);
	henk->f2 = false;
}

void	take_first_fork(t_data *data, t_philo *henk, t_fork *fork)
{
	int	time;

	time = 0;
	while (henk->f1 == false)
	{
		if (check_if_alive(henk, &henk->lock) == false)
			return ;
		pthread_mutex_lock(&fork->lock);
		if (fork->fork == AVAILABLE)
		{
			henk->fork1->fork = TAKEN;
			henk->f1 = true;
			time = get_runtime(data->start_time, &data->lock);
			printf("%d %d has taken a (1st) fork\n", time, henk->num);
		}
		pthread_mutex_unlock(&fork->lock);
		usleep(200);
	}
}

void	take_second_fork(t_data *data, t_philo *henk, t_fork *fork)
{
	int	time;

	time = 0;
	while (henk->f2 == false)
	{
		if (check_if_alive(henk, &henk->lock) == false)
			return ;
		pthread_mutex_lock(&fork->lock);
		if (fork->fork == AVAILABLE)
		{
			henk->fork2->fork = TAKEN;
			henk->f2 = true;
			time = get_runtime(data->start_time, &data->lock);
			printf("%d %d has taken a fork\n", time, henk->num);
		}
		pthread_mutex_unlock(&fork->lock);
		usleep(200);
	}
}
