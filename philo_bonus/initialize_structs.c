/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_structs.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/24 20:33:09 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	henk_data(t_data *data, t_philo *henk, sem_t *lock, int num)
{
	char	*str;

	henk->num = num;
	henk->num_eaten = 0;
	henk->last_eaten = 0;
	henk->max_eat = data->num_eat;
	henk->t_eat = data->t_eat;
	henk->t_die = data->t_die;
	henk->start_time = data->start_time;
	henk->alive = true;
	henk->saturated = false;
	henk->data = data;
	henk->forks = data->forks;
	henk->print = data->print;
	str = ft_philitoa(henk->num);
	sem_unlink(str);
	lock = sem_open(str, O_CREAT, 0644, 1);
	if (lock == SEM_FAILED)
		return (-1);
	henk->lock = lock;
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
	sem_t	**locks;

	i = 0;
	henk = malloc(data->ph_num * sizeof(t_philo));
	if (henk == NULL)
		return (-1);
	data->philos = henk;
	locks = malloc(data->ph_num * sizeof(sem_t *));
	if (locks == NULL)
		return (-1);
	while (i < data->ph_num)
	{
		if (henk_data(data, &henk[i], locks[i], i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_structs(t_data *data)
{
	if (init_semaphores(data) == -1)
		return (-1);
	data->start_time = get_time();
	if (init_philos(data) == -1)
		return (-1);
	return (0);
}
