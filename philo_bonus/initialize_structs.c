/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_structs.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/17 11:16:02 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sjon_data(t_data *data, t_philo *p, int num)
{
	p->num = num;
	p->num_eaten = 0;
	p->max_eat = data->num_eat;
	p->t_eat = data->t_eat * 1000;
	p->t_die = data->t_die * 1000;
	p->t_sleep = data->t_sleep * 1000;
	p->alive = true;
	p->saturated = false;
	p->data = data;
	p->forks = data->forks;
	p->print = data->print;
}

int	init_sjon(t_data *data, int num)
{
	t_philo	*sjon;
	char	*str;

	sjon = data->sjonnies[num];
	sjon_data(data, sjon, num);
	sjon->sem_id = ft_philitoa(sjon->num);
	if (sjon->sem_id == NULL)
		return (-1);
	sem_unlink(sjon->sem_id);
	sjon->poke = sem_open(sjon->sem_id, O_CREAT, 0644, 1);
	if (sjon->poke == SEM_FAILED)
		return (-1);
	sjon->last_eaten = get_time();
	sjon_is_born(data, num);
	return (0);
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
