/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/15 20:40:17 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/17 11:03:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	fork_process(t_data *data)
{
	int		i;
	pid_t	id;

	i = 0;
	id = 0;
	sem_wait(data->start);
	while (i < data->ph_num)
	{
		if (id == 0)
			id = fork();
		else
			break ;
		i++;
	}
	if (id != 0)
	{
		if (sjon_is_born(data, i) == -1)
			return (-1);
	}
	usleep(1000);
	sem_post(data->start);
	return (0);
}

static int	parse_input(t_data *data, int argc, char **argv)
{
	data->forks = NULL;
	data->print = NULL;
	data->ph_num = ft_philatoi(argv[1]);
	if (data->ph_num == 0)
		return (printf("Not enough philosophers 🤓\n"), -1);
	else if (data->ph_num > 999)
		return (printf("Too many philos to handle, sorry 🙂\n"), -1);
	data->sjonnies = malloc(data->ph_num * sizeof(t_philo *));
	if (data->sjonnies == NULL)
		return (-1);
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
		return (2);
	if (init_semaphores(&data) == -1)
		return (3);
	if (fork_process(&data) == -1)
	{
		
	}
	// if (run_threads(&data, data.philos) == -1)
	// {
	// 	clean_up(&data);
	// 	return (4);
	// }
	clean_up(&data);
	return (0);
}
