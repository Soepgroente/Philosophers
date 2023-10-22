/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/15 20:40:17 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/22 18:40:55 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	fork_process(t_data *data)
{
	pid_t	id;
	pid_t	*pids;

	id = 0;
	pids = ft_calloc(data->ph_num * sizeof(pid_t));
	if (pids == NULL)
		return (-1);
	sem_wait(data->start);
	while (data->num < data->ph_num)
	{
		id = fork();
		if (id == -1)
		{
			kill_children(pids, data->ph_num);
			return (-1);
		}
		if (id == 0)
			return (sjon_is_born(data));
		pids[data->num] = id;
		data->num++;
	}
	sem_post(data->start);
	return (0);
}

static int	parse_input(t_data *data, int argc, char **argv)
{
	data->forks = NULL;
	data->print = NULL;
	data->start = NULL;
	data->num = 0;
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
		return (4);
	else
	{
		waitpid(-1, NULL, 0);
		kill_children()
	}
	// if (run_threads(&data, data.philos) == -1)
	// {
	// 	clean_up(&data);
	// 	return (4);
	// }
	clean_up(&data);
	return (0);
}
