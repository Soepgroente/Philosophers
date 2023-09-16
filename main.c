/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 13:49:57 by vincent           #+#    #+#             */
/*   Updated: 2023/09/16 17:15:48 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pull_the_plug(t_data *data)
{
	int		i;
	t_philo	*p;

	i = 0;
	p = data->philos;
	while (i < data->ph_num)
	{
		p[i].alive = false;
		pthread_mutex_destroy(&p[i].lock);
		
	}
}

void	stalk_philos(t_data *data)
{
	int	i;
	
	while (INFINITY)
	{
		i = 0;
		data->time = (int)(get_time() - data->start_time) / 1000;
		if (data->num_eat != 0)
		{
			while (i < data->ph_num)
			{
				if (data->philos[i].saturated == false)
					break ;
				i++;
			}
			if (i == data->ph_num)
				pull_the_plug(data);
			return ;
		}
		i = 0;
		while (i < data->ph_num)
		{
			if (data->time - data->philos[i].last_eaten >= data->t_die)
			{
				data->time = (int)(get_time() - data->start_time) / 1000;
				pull_the_plug(data);
				printf("%d %d has died\n", data->time, data->philos[i].num);
				return ;
			}
			i++;
		}
		usleep(500);
	}
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
