/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/12 12:53:33 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data, t_philo *philo, int x)
{
	philo->num = x;
	philo->alive = true;
	if (x == 0)
	{
		philo->left_fork = data->forks[data->ph_num - 1];
		philo->right_fork = data->forks[0];
	}
	else
	{
		philo->left_fork = data->forks[x - 1];
		philo->right_fork = data->forks[x];
	}
}

int	create_threads(t_data *data)
{
	pthread_t	*philos;
	int			i;
	
	i = 0;
	philos = malloc((data->ph_num + 1) * sizeof(pthread_t));
	philos[data->ph_num] = NULL;
	pthread_mutex_init(&data->mutex, NULL);
	while (i < data->ph_num)
	{
		pthread_create(&philos[i], NULL, &some_function, data);
		i++;
	}
	i = 0;
	while (i < data->ph_num)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	return (0);
}

int	parse_input(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->ph_num = ft_philatoi(argv[1]);
	if (data->ph_num == 0)
		return (printf("Not enough philosophers\n"), -1);
	data->t_die = ft_philatoi(argv[2]);
	data->t_eat = ft_philatoi(argv[3]);
	data->t_sleep = ft_philatoi(argv[4]);
	data->num_eat = 0;
	if (argc == 6)
		data->num_eat = ft_philatoi(argv[5]);
	if (data->ph_num == -1 || data->t_die == -1 || data->t_eat == -1 || \
		data->t_sleep == -1 || data->num_eat == -1)
		return (-1);
	data->forks = malloc((data->ph_num + 1) * sizeof(int));
	while (i < data->ph_num)
	{
		data->forks[i] = i;
		i++;
	}
	data->forks[i] = -1;
	data->x = 0;
	return (0);
}