/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/31 11:44:44 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *sjon, char *msg)
{
	sem_wait(sjon->print);
	if (poke_sjon(sjon) == false)
	{
		sem_post(sjon->print);
		return ;
	}
	printf("%d %d %s", get_runtime(sjon->t_start), sjon->num, msg);
	sem_post(sjon->print);
}

bool	poke_sjon(t_philo *sjon)
{
	if (sjon->alive == false)
		return (false);
	if (sjon->t_die < get_time() - sjon->last_eaten)
	{
		sjon->alive = false;
		return (false);
	}
	return (true);
}

void	kill_sjon(t_philo *sjon)
{
	sjon->alive = false;
}