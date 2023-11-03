/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_structs.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/02 16:27:21 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sjon_data(t_data *data, t_philo *sjon, int num)
{
	sjon->num = num;
	sjon->num_eaten = 0;
	sjon->max_eat = data->num_eat;
	sjon->t_eat = data->t_eat * 1000;
	sjon->t_die = data->t_die * 1000;
	sjon->t_sleep = data->t_sleep * 1000;
	sjon->alive = true;
	sjon->death = data->death;
	sjon->forks = data->forks;
	sjon->print = data->print;
	sjon->saturated = data->saturated;
	sjon->start = data->start;
	sjon->t_start = data->t_start;
	sjon->last_eaten = data->t_start;
}

t_philo	*init_sjon(t_data *data)
{
	t_philo	*sjon;

	sjon = malloc(sizeof(t_philo));
	if (sjon == NULL)
		return (NULL);
	sjon_data(data, sjon, data->num);
	return (sjon);
}

int	init_semaphores(t_data *data)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_start");
	sem_unlink("/sem_death");
	sem_unlink("/sem_saturated");
	data->forks = sem_open("/sem_forks", O_CREAT, 0644, data->ph_num);
	data->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	data->start = sem_open("/sem_start", O_CREAT, 0644, 0);
	data->death = sem_open("/sem_death", O_CREAT, 0644, 0);
	data->saturated = sem_open("/sem_saturated", O_CREAT, 0644, 0);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED || \
	data->start == SEM_FAILED || data->death == SEM_FAILED || \
	data->saturated == SEM_FAILED)
		return (-1);
	return (0);
}
