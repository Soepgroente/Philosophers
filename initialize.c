/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:14:57 by vvan-der          #+#    #+#             */
/*   Updated: 2023/09/16 17:17:15 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	int	i;
	t_philo		*subjects;

	i = 0;
	subjects = malloc(data->ph_num * sizeof(t_philo));
	if (!subjects)
		return (-1);
	while (i < data->ph_num)
		data->forks[i++] = AVAILABLE;
	i = 0;
	while (i < data->ph_num)
	{
		init_philo(data, &subjects[i], i);
		data->philos[i] = subjects[i];
	}
	return (0);
}

void	init_philo(t_data *data, t_philo *philo, int x)
{
	philo->num = x;
	philo->num_eaten = 0;
	philo->lf = false;
	philo->rf = false;
	philo->alive = true;
	pthread_mutex_init(&philo->lock, NULL);
	if (x == 0)
	{
		philo->left_fork = &data->forks[data->ph_num - 1];
		philo->right_fork = &data->forks[0];
		printf("Fork (left) init by philo %d: %d\n", x, *philo->left_fork);
		printf("Fork (right) init by philo %d: %d\n", x, *philo->right_fork);
	}
	else
	{
		philo->left_fork = &data->forks[x - 1];
		philo->right_fork = &data->forks[x];
		printf("Fork (left) init by philo %d: %d\n", x, *philo->left_fork);
		printf("Fork (right) init by philo %d: %d\n", x, *philo->right_fork);
	}
	data->philos[x] = *philo;
}

int	create_threads(t_data *data)
{
	pthread_t	*threads;
	int			i;
	
	i = 0;
	threads = malloc((data->ph_num + 1) * sizeof(pthread_t));
	if (!threads)
		return (-1);
	threads[data->ph_num] = NULL;
	init_data(data);
	while (i < data->ph_num)
	{
		pthread_create(&threads[i], NULL, &start_routine, (void *) data);
		i++;
	}
	data->ready = true;
	stalk_philos(data);
	i = 0;
	while (i < data->ph_num)
	{
		pthread_join(threads[i], NULL);
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
	if (argc == 6)
		data->num_eat = ft_philatoi(argv[5]);
	else
		data->num_eat = -42;
	if (data->ph_num == -1 || data->t_die == -1 || data->t_eat == -1 || \
		data->t_sleep == -1 || data->num_eat == -1)
		return (-1);
	data->forks = malloc((data->ph_num) * sizeof(bool));
	while (i < data->ph_num)
	{
		data->forks[i] = false;
		i++;
	}
	data->x = 0;
	data->ready = false;
	return (0);
}