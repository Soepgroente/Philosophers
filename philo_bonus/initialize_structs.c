/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_structs.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/24 10:44:54 by vvan-der      ########   odam.nl         */
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
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_start");
	sem_unlink("/sem_death");
	sem_unlink("/sem_saturated");
	data->forks = sem_open("/sem_forks", O_CREAT, 0644, data->ph_num);
	data->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	data->start = sem_open("/sem_start", O_CREAT, 0644, 0);
	data->death = sem_open("/sem_death", O_CREAT, 0644, 1);
	data->saturated = sem_open("/sem_saturated", O_CREAT, 0644, 1);
	return (0);
}
