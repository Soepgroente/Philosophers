/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:28:03 by vvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 15:56:45 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_if_saturated(t_philo *henk, pthread_mutex_t *lock)
{
	bool	saturated;

	pthread_mutex_lock(lock);
	if (henk->saturated == true)
		saturated = true;
	else
		saturated = false;
	pthread_mutex_unlock(lock);
	return (saturated);
}

bool	check_if_alive(t_philo *henk, pthread_mutex_t *lock, bool action)
{
	int	time;

	time = get_runtime(henk->start_time);
	pthread_mutex_lock(lock);
	if (action == KILL)
		henk->alive = false;
	if (henk->alive == false)
	{
		pthread_mutex_unlock(lock);
		return (false);
	}
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

void	take_first_fork(t_philo *henk, t_fork *fork)
{
	int	time;

	time = 0;
	while (henk->f1 == false)
	{
		if (check_if_alive(henk, &henk->lock, NONE) == false)
			return ;
		pthread_mutex_lock(&fork->lock);
		if (fork->fork == AVAILABLE)
		{
			henk->fork1->fork = TAKEN;
			henk->f1 = true;
			time = get_runtime(henk->start_time);
			printf("%d %d has taken a fork\n", time, henk->num);
		}
		pthread_mutex_unlock(&fork->lock);
		usleep(100);
	}
}

void	take_second_fork(t_philo *henk, t_fork *fork)
{
	int	time;

	time = 0;
	while (henk->f2 == false)
	{
		if (check_if_alive(henk, &henk->lock, NONE) == false)
			return ;
		pthread_mutex_lock(&fork->lock);
		if (fork->fork == AVAILABLE)
		{
			henk->fork2->fork = TAKEN;
			henk->f2 = true;
			time = get_runtime(henk->start_time);
			printf("%d %d has taken a fork\n", time, henk->num);
		}
		pthread_mutex_unlock(&fork->lock);
		usleep(100);
	}
}
