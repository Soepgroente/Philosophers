/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:28:03 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/04 19:02:05 by vincent       ########   odam.nl         */
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
	printf("%d %d %s", get_runtime(sjon->t_start), sjon->num + 1, msg);
	sem_post(sjon->print);
}

bool	poke_sjon(t_philo *sjon)
{
	if (sjon->alive == false)
		return (false);
	if (sjon->t_die < get_time() - sjon->last_eaten)
	{
		sem_post(sjon->death);
		sem_wait(sjon->freeze);
		printf("%d %d has died\n", get_runtime(sjon->t_start), sjon->num + 1);
		free(sjon);
		exit(EXIT_SUCCESS);
	}
	return (true);
}

void	kill_sjon(t_philo *sjon)
{
	sjon->alive = false;
}
