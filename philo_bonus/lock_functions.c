/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/24 22:13:01 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *henk, char *msg)
{
	sem_wait(henk->print);
	printf("%d %d %s", get_runtime(henk->start_time), henk->num, msg);
	sem_post(henk->print);
}

bool	check_if_saturated(t_philo *henk, sem_t *lock, bool eaten)
{
	bool	saturated;

	sem_wait(lock);
	if (eaten == true)
		henk->num_eaten++;
	if (henk->num_eaten == henk->max_eat)
		saturated = true;
	if (henk->saturated == true)
		saturated = true;
	else
		saturated = false;
	sem_post(lock);
	return (saturated);
}

bool	check_last_eaten(t_philo *henk, sem_t *lock, bool eaten)
{
	bool	alive;

	sem_wait(lock);
	if (eaten == true)
		henk->last_eaten = get_runtime(henk->start_time);
	if (henk->t_die <= get_runtime(henk->start_time) - henk->last_eaten)
		alive = false;
	else
		alive = true;
	sem_post(lock);
	return (alive);
}

bool	poke_henk(t_philo *henk, sem_t *lock, bool action)
{
	bool	alive;
	
	sem_wait(lock);
	if (action == KILL || henk->alive == false)
		alive = false;
	else
		alive = true;
	sem_post(lock);
	return (alive);
}