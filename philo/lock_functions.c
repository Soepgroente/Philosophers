/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/09 11:26:47 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_if_saturated(t_philo *henk, pthread_mutex_t *lock)
{
	bool	saturated;

	pthread_mutex_lock(lock);
	if (henk->num_eaten >= henk->max_eat)
	{
		henk->saturated = true;
		saturated = true;
	}
	else
		saturated = false;
	pthread_mutex_unlock(lock);
	return (saturated);
}

bool	poke_henk(t_philo *henk, pthread_mutex_t *lock, bool action)
{
	pthread_mutex_lock(lock);
	if (action == KILL || henk->alive == false || \
	henk->t_die < get_runtime(henk->t_start) - henk->last_eaten)
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

void	take_forks(t_philo *henk)
{
	pthread_mutex_lock(&henk->fork1->lock);
	print_message(henk, &henk->data->print_lock, "has taken a fork\n");
	pthread_mutex_lock(&henk->fork2->lock);
	print_message(henk, &henk->data->print_lock, "has taken a fork\n");
	eat_foods(henk);
	ft_sleep(henk, henk->t_eat * 1000);
	pthread_mutex_unlock(&henk->fork2->lock);
	pthread_mutex_unlock(&henk->fork1->lock);
}

void	eat_foods(t_philo *henk)
{
	if (poke_henk(henk, &henk->life_lock, NONE) == false)
		return ;
	print_message(henk, &henk->data->print_lock, "is eating\n");
	pthread_mutex_lock(&henk->food_lock);
	henk->num_eaten++;
	henk->last_eaten = get_runtime(henk->t_start);
	pthread_mutex_unlock(&henk->food_lock);
}
