/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 13:49:57 by vincent       #+#    #+#                 */
/*   Updated: 2023/09/11 15:55:57 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*some_function(void *data)
{
	t_data	*d;

	d = (t_data *) data;
	printf("Thread: %d\n", d->i);
	printf("T_die: %d\n", d->t_die);
	printf("Eattime: %d\n", d->t_eat);
	printf("Sleep: %d\n", d->t_sleep);
	printf("# of eat: %d\n", d->num_eat);
	return (NULL);
}

static int	create_threads(t_data *d)
{
	pthread_t	*philos;
	
	d->i = 0;
	philos = malloc((d->ph_num + 1) * sizeof(pthread_t));
	philos[d->ph_num] = NULL;
	while (d->i < d->ph_num)
	{
		pthread_create(&philos[d->i], NULL, &some_function, d);
		usleep(100);
		(d->i)++;
	}
	d->i = 0;
	while (d->i < d->ph_num)
	{
		pthread_join(philos[d->i], NULL);
		d->i++;
	}
	return (0);
}

static int	parse_input(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->ph_num = ft_philatoi(argv[1]);
	data->t_die = ft_philatoi(argv[2]);
	data->t_eat = ft_philatoi(argv[3]);
	data->t_sleep = ft_philatoi(argv[4]);
	data->num_eat = 0;
	if (argc == 6)
		data->num_eat = ft_philatoi(argv[5]);
	if (data->ph_num == -1 || data->t_die == -1 || data->t_eat == -1 || \
		data->t_sleep == -1 || data->num_eat == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Please insert # of philos, time to die, time to eat, time to sleep \
		and optionally # of times each philo eats\n");
		return (1);
	}
	if (parse_input(&data, argc, argv) == -1)
		return (1);
	if (create_threads(&data) == -1)
		return (1);
	return (0);
}