/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_structs.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/22 18:18:23 by vincent       ########   odam.nl         */
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
	sjon->saturated = false;
	sjon->forks = data->forks;
	sjon->print = data->print;
}

t_philo	*init_sjon(t_data *data)
{
	
}

int	init_semaphores(t_data *data)
{
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_start");
	data->forks = sem_open("/sem_fork", O_CREAT, 0644, data->ph_num);
	if (data->forks == SEM_FAILED)
		return (-1);
	data->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_unlink("/sem_fork");
		return (-1);
	}
	data->start = sem_open("/sem_start", O_CREAT, 0644, 1);
	if (data->start == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->print);
		sem_unlink("/sem_print");
		sem_unlink("/sem_start");
		return (-1);
	}
	return (0);
}
