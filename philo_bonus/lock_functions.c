/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/30 18:08:03 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *sjon, char *msg)
{
	if (poke_sjon(sjon, sjon->lock, NONE) == false)
		return ;
	sem_wait(sjon->print);
	printf("%d %d %s", get_runtime(sjon->t_start), sjon->num, msg);
	sem_post(sjon->print);
}

bool	check_if_saturated(t_philo *sjon, sem_t *lock)
{
	bool	saturated;

	sem_wait(lock);
	if (sjon->saturated == true || sjon->num_eaten >= sjon->max_eat)
	{
		sjon->saturated = true;
		saturated = true;
	}
	else
		saturated = false;
	sem_post(lock);
	return (saturated);
}

bool	check_last_eaten(t_philo *sjon, sem_t *lock, bool eaten)
{
	bool	alive;

	alive = true;
	sem_wait(lock);
	if (sjon->t_die <= get_time() - sjon->last_eaten)
		alive = false;
	else if (eaten == true)
	{
		sjon->last_eaten = get_time();
		sjon->num_eaten++;
	}
	sem_post(lock);
	return (alive);
}

bool	poke_sjon(t_philo *sjon, sem_t *lock, bool action)
{
	bool	alive;

	sem_wait(lock);
	if (action == KILL || sjon->alive == false)
	{
		sjon->alive = false;
		alive = false;
	}
	else
		alive = true;
	sem_post(lock);
	return (alive);
}
