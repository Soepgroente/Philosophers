/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 13:49:57 by vincent           #+#    #+#             */
/*   Updated: 2023/08/13 18:01:06 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->philos = ft_philatoi(argv[1]);
	data->t_die = ft_philatoi(argv[2]);
	data->t_eat = ft_philatoi(argv[3]);
	data->t_sleep = ft_philatoi(argv[4]);
	data->num_eat = 0;
	if (argc == 6)
		data->num_eat = ft_philatoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Please insert # of philos, time to die, time to eat, time to sleep \
		and optionally # of times each philo eats");
		return (1);
	}
	parse_input(&data, argc, argv);
}