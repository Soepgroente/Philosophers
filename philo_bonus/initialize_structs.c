/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_structs.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/15 23:29:48 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sjon_data2(t_data *data, t_philo *p, int num)
{
	p->num = num;
	p->num_eaten = 0;
	p->last_eaten = 0;
	p->max_eat = data->num_eat;
	p->t_eat = data->t_eat;
	p->t_die = data->t_die;
	if (data->t_eat == 0 || data->t_sleep == 0)
		p->t_think = 1;
	else
		p->t_think = 0;
	p->alive = true;
	p->saturated = false;
	p->data = data;
	p->forks = data->forks;
	p->print = data->print;
}

static int	sjon_data(t_data *data, t_philo *p, int num)
{
	char	*str1;
	char	*str2;
	char	*str3;

	sjon_data2(data, p, num);
	str1 = ft_philitoa(p->num);
	str2 = ft_philitoa(p->num + data->ph_num);
	str3 = ft_philitoa(p->num + (data->ph_num * 2));
	if (str1 == NULL || str2 == NULL || str3 == NULL)
		return (-1);
	sem_unlink(str1);
	sem_unlink(str2);
	sem_unlink(str3);
	p->poke = sem_open(str1, O_CREAT, 0644, 1);
	p->eat = sem_open(str2, O_CREAT, 0644, 1);
	p->eat2 = sem_open(str3, O_CREAT, 0644, 1);
	if (p->poke == SEM_FAILED || p->eat == SEM_FAILED || p->eat2 == SEM_FAILED)
		return (-1);
	free(str1);
	free(str2);
	free(str3);
	return (0);
}

static int	init_semaphores(t_data *data)
{
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
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
	return (0);
}

static int	init_philos(t_data *data)
{
	int		i;
	t_philo	*sjon;

	i = 0;
	sjon = malloc(data->ph_num * sizeof(t_philo));
	if (sjon == NULL)
		return (-1);
	data->philos = sjon;
	while (i < data->ph_num)
	{
		if (sjon_data(data, &sjon[i], i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_structs(t_data *data)
{
	if (init_semaphores(data) == -1)
		return (-1);
	if (init_philos(data) == -1)
		return (-1);
	return (0);
}
