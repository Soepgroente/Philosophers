/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:14:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/19 11:43:13 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data, t_philo *philo, int x)
{
	philo->num = x;
	philo->num_eaten = 0;
	philo->lf = false;
	philo->rf = false;
	philo->alive = true;
	philo->data = data;
	if (pthread_mutex_init(&philo->lock, NULL) == -1)
		return (-1);
	if (x == 0)
	{
		philo->left_fork = &data->forks[data->ph_num - 1];
		philo->right_fork = &data->forks[0];
		// printf("Fork (left)  init by philo %d: %d, address: %p\n", x, *philo->left_fork, philo->left_fork);
		// printf("Fork (right) init by philo %d: %d, address: %p\n", x, *philo->right_fork, philo->right_fork);
	}
	else
	{
		philo->left_fork = &data->forks[x - 1];
		philo->right_fork = &data->forks[x];
		// printf("Fork (left)  init by philo %d: %d, address: %p\n", x, *philo->left_fork, philo->left_fork);
		// printf("Fork (right) init by philo %d: %d, address: %p\n", x, *philo->right_fork, philo->right_fork);
	}
	return (0);
}

static t_philo	*make_puppets(t_data *data)
{
	int		i;
	t_philo	*subjects;

	i = 0;
	subjects = malloc(data->ph_num * sizeof(t_philo));
	if (!subjects)
		return (NULL);
	while (i < data->ph_num)
		data->forks[i++] = AVAILABLE;
	i = 0;
	while (i < data->ph_num)
	{
		init_philo(data, &subjects[i], i);
		i++;
	}
	return (subjects);
}

int	create_threads(t_data *data)
{
	pthread_t	*threads;
	t_philo		*philos;
	int			i;
	
	i = 0;
	threads = malloc((data->ph_num) * sizeof(pthread_t));
	if (!threads)
		return (-1);
	philos = make_puppets(data);
	data->philos = philos;
	while (i < data->ph_num)
	{
		pthread_create(&threads[i], NULL, &start_routine, (void *) &philos[i]);
		i++;
	}
	usleep(100);
	data->start_time = get_time();
	on_your_marks(true, data, &data->lock);
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
	data->time = 0;
	pthread_mutex_init(&data->lock, NULL);
	data->ready = false;
	return (0);
}
