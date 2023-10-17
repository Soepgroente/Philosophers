/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/16 12:20:39 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *sjon, char *msg)
{
	sem_wait(sjon->print);
	if (poke_sjon(sjon, sjon->poke) == false)
	{
		sem_post(sjon->print);
		return ;
	}
	printf("%d %d %s", get_runtime(sjon->t_start), sjon->num, msg);
	sem_post(sjon->print);
}

bool	poke_sjon(t_philo *sjon, sem_t *poke)
{
	sem_wait(poke);
	if (sjon->alive == false)
	{
		sem_post(poke);
		return (false);
	}
	if (sjon->t_die < get_time() - sjon->last_eaten)
	{
		sjon->alive = false;
		sem_post(poke);
		return (false);
	}
	sem_post(poke);
	return (true);
}

void	kill_sjon(t_philo *sjon, sem_t *poke)
{
	sem_wait(poke);
	sjon->alive = false;
	sem_post(poke);
}