/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/24 20:39:42 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *henk, char *msg)
{
	sem_wait(henk->print);
	printf("%d %d %s", get_runtime(henk->start_time), henk->num, msg);
	sem_post(henk->print);
}

bool	poke_henk(t_philo *henk, sem_t *lock, bool action)
{
	sem_wait(lock);
	if (action == KILL)
		henk->alive = false;
	if (henk->alive == false)
	{
		sem_post(lock);
		return (false);
	}
	if (henk->t_die <= get_runtime(henk->start_time) - henk->last_eaten)
	{
		henk->alive = false;
		sem_post(lock);
		return (false);
	}
	else
	{
		sem_post(lock);
		return (true);
	}
}