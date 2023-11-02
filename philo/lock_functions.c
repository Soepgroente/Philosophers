/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/02 14:14:34 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_if_saturated(t_philo *henk, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	if (henk->num_eaten >= henk->max_eat)
	{
		henk->saturated = true;
		pthread_mutex_unlock(lock);
		return (true);
	}
	pthread_mutex_unlock(lock);
	return (false);
}

bool	poke_henk(t_philo *henk)
{
	pthread_mutex_lock(&henk->lock);
	if (henk->alive == false)
	{
		pthread_mutex_unlock(&henk->lock);
		return (false);
	}
	if (henk->t_die < get_time() - henk->last_eaten)
	{
		henk->alive = false;
		pthread_mutex_unlock(&henk->lock);
		return (false);
	}
	pthread_mutex_unlock(&henk->lock);
	return (true);
}

void	eat_foods(t_philo *henk)
{
	if (poke_henk(henk) == false)
		return ;
	print_message(henk, &henk->data->print_lock, "is eating\n");
	pthread_mutex_lock(&henk->lock);
	henk->num_eaten++;
	henk->last_eaten = get_time();
	pthread_mutex_unlock(&henk->lock);
	power_naps(henk, henk->t_eat);
}

void	print_message(t_philo *henk, pthread_mutex_t *print_lock, char *msg)
{
	pthread_mutex_lock(print_lock);
	if (poke_henk(henk) == false)
	{
		pthread_mutex_unlock(print_lock);
		return ;
	}
	printf("%d %d %s", get_runtime(henk->t_start), henk->num + 1, msg);
	pthread_mutex_unlock(print_lock);
}

void	kill_henk(t_philo *henk, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	henk->alive = false;
	pthread_mutex_unlock(lock);
}
