/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/06 12:58:35 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_semaphores(t_data *data)
{
	sem_close(data->death);
	sem_close(data->forks);
	sem_close(data->freeze);
	sem_close(data->print);
	sem_close(data->saturated);
	sem_close(data->start);
	sem_unlink("/sem_death");
	sem_unlink("/sem_forks");
	sem_unlink("/sem_freeze");
	sem_unlink("/sem_print");
	sem_unlink("/sem_saturated");
	sem_unlink("/sem_start");
}

void	clean_up(t_data *data, t_philo *philo)
{
	unlink_semaphores(data);
	free(data->processes);
	if (philo != NULL)
		free(philo);
}
