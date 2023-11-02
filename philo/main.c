/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 13:49:57 by vincent       #+#    #+#                 */
/*   Updated: 2023/11/02 13:41:48 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_input(t_data *data, int argc, char **argv)
{
	data->forks = NULL;
	data->philos = NULL;
	data->go = false;
	data->ph_num = ft_philatoi(argv[1]);
	if (data->ph_num == 0)
		return (printf("Not enough philosophers 🤓\n"), -1);
	else if (data->ph_num > 999)
		return (printf("Too many philos to handle, sorry 🙂\n"), -1);
	data->t_die = ft_philatoi(argv[2]);
	data->t_eat = ft_philatoi(argv[3]);
	data->t_sleep = ft_philatoi(argv[4]);
	if (argc == 6)
		data->num_eat = ft_philatoi(argv[5]);
	else
		data->num_eat = INT_MAX;
	if (data->ph_num == -1 || data->t_die == -1 || data->t_eat == -1 || \
		data->t_sleep == -1 || data->num_eat == -1)
	{
		printf("Error: invalid input 😕\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Please insert # of philos, time to die, time to eat, ");
		printf("time to sleep and optionally # of times each philo eats\n");
		return (1);
	}
	if (parse_input(&data, argc, argv) == -1)
		return (2);
	if (init_structs(&data) == -1)
		return (3);
	if (thread_carefully(&data, data.philos) == -1)
	{
		clean_up(&data);
		return (4);
	}
	clean_up(&data);
	return (0);
}
