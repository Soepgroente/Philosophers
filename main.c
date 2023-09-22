/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 13:49:57 by vincent           #+#    #+#             */
/*   Updated: 2023/09/22 17:15:39 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_everyone(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		check_if_alive(&data->philos[i], &data->philos[i].lock, KILL);
		i++;
	}
}

void	stalk_philos(t_data *data)
{
	int	i;
	int	time;

	while (INFINITY)
	{
		i = 0;
		// time = get_runtime(data->start_time);
		while (i < data->ph_num)
		{
			if (check_if_alive(&data->philos[i], &data->philos[i].lock, NONE) == false)
			{
				kill_everyone(data);
				usleep(1000);
				time = get_runtime(data->start_time);
				printf("%d %d has died\n", time, i);
				return ;
			}
			if (check_if_saturated(&data->philos[i], &data->philos[i].lock) == true)
			{
				kill_everyone(data);
				time = get_runtime(data->start_time);
				printf("Number of times eaten: %d\n", data->philos[i].num_eaten);
				return ;
			}
			i++;
		}
	}
}

static int	parse_input(t_data *data, int argc, char **argv)
{
	data->forks = NULL;
	data->philos = NULL;
	data->ph_num = ft_philatoi(argv[1]);
	if (data->ph_num == 0)
		return (printf("Not enough philosophers\n"), -1);
	data->t_die = ft_philatoi(argv[2]);
	data->t_eat = ft_philatoi(argv[3]);
	data->t_sleep = ft_philatoi(argv[4]);
	if (argc == 6)
		data->num_eat = ft_philatoi(argv[5]);
	else
		data->num_eat = INT_MAX;
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
	{
		clean_up(&data);
		return (2);
	}
	if (init_structs(&data) == -1)
	{
		clean_up(&data);
		return (3);
	}
	if (run_threads(&data) == -1)
	{
		clean_up(&data);
		return (4);
	}
	// clean_up(&data);
	return (0);
}
