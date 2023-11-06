/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/15 20:40:17 by vincent       #+#    #+#                 */
/*   Updated: 2023/11/06 12:53:56 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	not_much_of_a_simulation(t_data *data)
{
	data->t_start = get_time();
	printf("%d %d is thinking\n", get_runtime(data->t_start), 1);
	printf("%d %d has taken a fork\n", get_runtime(data->t_start), 1);
	usleep(data->t_die * 1000);
	printf("%d %d has died\n", get_runtime(data->t_start), 1);
	exit(EXIT_SUCCESS);
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
	if (data->ph_num == 1)
		not_much_of_a_simulation(data);
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
	if (wait_for_ending(&data) != 0)
		printf("Simulation has gone wrong\n");
	simulation_end(&data);
	clean_up(&data, NULL);
	return (0);
}
