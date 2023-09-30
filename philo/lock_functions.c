/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/30 17:02:39 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_if_saturated(t_philo *henk, pthread_mutex_t *lock)
{
	bool	saturated;

	pthread_mutex_lock(lock);
	if (henk->num_eaten >= henk->max_eat)
		henk->saturated = true;
	if (henk->saturated == true)
		saturated = true;
	else
		saturated = false;
	pthread_mutex_unlock(lock);
	return (saturated);
}

bool	poke_henk(t_philo *henk, pthread_mutex_t *lock, bool action)
{
	pthread_mutex_lock(lock);
	if (action == KILL)
		henk->alive = false;
	if (henk->alive == false || henk->t_die < get_time() - henk->last_eaten)
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

void	return_forks(t_fork *fork1, t_fork *fork2)
{
	pthread_mutex_lock(&fork1->lock);
	fork1->fork = AVAILABLE;
	pthread_mutex_unlock(&fork1->lock);
	pthread_mutex_lock(&fork2->lock);
	fork2->fork = AVAILABLE;
	pthread_mutex_unlock(&fork2->lock);
}

bool	take_first_fork(t_philo *henk, t_fork *fork)
{
	while (INFINITY)
	{
		if (poke_henk(henk, &henk->lock, NONE) == false)
			return (false);
		pthread_mutex_lock(&fork->lock);
		if (fork->fork == AVAILABLE)
		{
			henk->fork1->fork = TAKEN;
			print_message(henk, &henk->data->print_lock, "has taken a fork\n");
			pthread_mutex_unlock(&fork->lock);
			return (true);
		}
		pthread_mutex_unlock(&fork->lock);
		usleep(200);
	}
}

bool	take_second_fork(t_philo *henk, t_fork *fork)
{
	while (INFINITY)
	{
		if (poke_henk(henk, &henk->lock, NONE) == false)
			return (false);
		pthread_mutex_lock(&fork->lock);
		if (fork->fork == AVAILABLE)
		{
			henk->fork2->fork = TAKEN;
			print_message(henk, &henk->data->print_lock, "has taken a fork\n");
			pthread_mutex_unlock(&fork->lock);
			return (true);
		}
		pthread_mutex_unlock(&fork->lock);
		usleep(200);
	}
}
