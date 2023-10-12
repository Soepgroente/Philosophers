/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/12 21:25:55 by vvan-der      ########   odam.nl         */
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

bool	poke_henk(t_philo *henk, pthread_mutex_t *life_lock)
{
	pthread_mutex_lock(life_lock);
	if (henk->alive == false || henk->t_die < get_time() - henk->last_eaten)
	{
		henk->alive = false;
		pthread_mutex_unlock(life_lock);
		return (false);
	}
	pthread_mutex_unlock(life_lock);
	return (true);
}

void	take_forks(t_philo *henk)
{
	pthread_mutex_lock(&henk->fork1->lock);
	if (henk->data->ph_num > 1)
	{
		print_message(henk, &henk->data->print_lock, "has taken a fork\n");
		pthread_mutex_lock(&henk->fork2->lock);
		print_message(henk, &henk->data->print_lock, "has taken a fork\n");
		eat_foods(henk);
		power_naps(henk, henk->t_eat * 1000);
		pthread_mutex_unlock(&henk->fork2->lock);
	}
	pthread_mutex_unlock(&henk->fork1->lock);
}

void	eat_foods(t_philo *henk)
{
	if (poke_henk(henk, &henk->life_lock) == false)
		return ;
	print_message(henk, &henk->data->print_lock, "is eating\n");
	pthread_mutex_lock(&henk->life_lock);
	henk->num_eaten++;
	henk->last_eaten = get_time();
	pthread_mutex_unlock(&henk->life_lock);
}
