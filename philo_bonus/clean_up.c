/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/24 10:58:54 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_semaphores(t_data *data)
{
	if (data->forks != SEM_FAILED)
	{
		sem_close(data->forks);
		sem_unlink("/sem_forks");
	}
	if (data->print != SEM_FAILED)
	{
		sem_close(data->print);
		sem_unlink("/sem_print");
	}
	if (data->start != SEM_FAILED)
	{
		sem_close(data->start);
		sem_unlink("/sem_start");
	}
	if (data->death != SEM_FAILED)
	{
		sem_close(data->death);
		sem_unlink("/sem_death");
	}
	if (data->saturated != SEM_FAILED)
	{
		sem_close(data->saturated);
		sem_unlink("/sem_saturated");
	}
}

void	clean_up(t_data *data, t_philo *philo)
{
	unlink_semaphores(data);
	if (philo != NULL)
		free(philo);
}
