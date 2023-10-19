/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/19 13:47:33 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->start);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_start");
	data->forks = NULL;
	data->print = NULL;
	data->start = NULL;
}

static void	free_sjonnie(t_philo *sjon, int num)
{
	sem_close(sjon->poke);
	sem_unlink(sjon->sem_id);
	free(sjon->sem_id);
	free(sjon);
	sjon = NULL;
}

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	if (data->sjonnies != NULL)
	{
		while (i < data->ph_num)
		{
			free_sjonnie(data->sjonnies[i], data->sjonnies[i]->num);
			i++;
		}
	}
	unlink_semaphores(data);
}
