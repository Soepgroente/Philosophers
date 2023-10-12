/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/09 17:32:49 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *sjon, char *msg)
{
	if (poke_sjon(sjon, sjon->poke, NONE) == false)
		return ;
	sem_wait(sjon->print);
	printf("%d %d %s", get_runtime(sjon->t_start), sjon->num, msg);
	sem_post(sjon->print);
}

int	check_last_eaten(t_philo *sjon, sem_t *eat, bool eaten)
{
	sem_wait(eat);
	if (sjon->t_die < (get_runtime(sjon->t_start) - sjon->last_eaten))
	{
		poke_sjon(sjon, sjon->poke, KILL);
		sem_post(eat);
		return (-1);
	}
	if (sjon->saturated == true)
	{
		sem_post(eat);
		return (1);
	}
	if (eaten == true)
	{
		sjon->last_eaten = get_runtime(sjon->t_start);
		sjon->num_eaten++;
		if (sjon->num_eaten >= sjon->max_eat)
		{
			sjon->saturated = true;
			sem_post(eat);
			return (1);
		}
	}
	sem_post(eat);
	return (0);
}

bool	poke_sjon(t_philo *sjon, sem_t *poke, bool action)
{
	sem_wait(poke);
	if (action == KILL || sjon->alive == false)
	{
		sjon->alive = false;
		sem_post(poke);
		return (false);
	}
	sem_post(poke);
	return (true);
}
