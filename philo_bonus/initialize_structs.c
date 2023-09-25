/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_structs.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 11:14:37 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	henk_data2(t_data *data, t_philo *p, int num)
{
	p->num = num;
	p->num_eaten = 0;
	p->last_eaten = 0;
	p->max_eat = data->num_eat;
	p->t_eat = data->t_eat;
	p->t_die = data->t_die;
	p->t_start = data->t_start;
	p->alive = true;
	p->saturated = false;
	p->data = data;
	p->forks = data->forks;
	p->print = data->print;
}

static int	henk_data(t_data *data, t_philo *p, int num)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = ft_philitoa(p->num);
	str2 = ft_philitoa(p->num + data->ph_num);
	str3 = ft_philitoa(p->num + data->ph_num * 2);
	sem_unlink(str1);
	sem_unlink(str2);
	sem_unlink(str3);
	p->lock = sem_open(str1, O_CREAT, 0644, 1);
	p->eat = sem_open(str2, O_CREAT, 0644, 1);
	p->eat2 = sem_open(str2, O_CREAT, 0644, 1);
	if (p->lock == SEM_FAILED || p->eat == SEM_FAILED || p->eat2 == SEM_FAILED)
		return (-1);
	henk_data2(data, p, num);
	return (0);
}

static int	init_semaphores(t_data *data)
{
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	data->forks = sem_open("/sem_fork", O_CREAT, 0644, data->ph_num);
	data->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED)
		return (-1);
	return (0);
}

static int	init_philos(t_data *data)
{
	int		i;
	t_philo	*henk;

	i = 0;
	henk = malloc(data->ph_num * sizeof(t_philo));
	if (henk == NULL)
		return (-1);
	data->philos = henk;
	while (i < data->ph_num)
	{
		if (henk_data(data, &henk[i], i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_structs(t_data *data)
{
	if (init_semaphores(data) == -1)
		return (-1);
	data->t_start = get_time();
	if (init_philos(data) == -1)
		return (-1);
	return (0);
}
