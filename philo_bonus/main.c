/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 13:49:57 by vincent       #+#    #+#                 */
/*   Updated: 2023/09/25 12:28:54 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_everyone(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		poke_henk(&data->philos[i], (&data->philos[i])->lock, KILL);
		i++;
	}
}

static void	just_for_norm(t_data *data, int i)
{
	kill_everyone(data);
	usleep(1000);
	printf("# of times eaten: %d\n", data->philos[i].num_eaten);
}

void	stalk_philos(t_data *d)
{
	while (INFINITY)
	{
		d->i = 0;
		while (d->i < d->ph_num)
		{
			if (poke_henk(&d->philos[d->i], \
			(&d->philos[d->i])->lock, NONE) == false || check_last_eaten \
			(&d->philos[d->i], (&d->philos[d->i])->eat, false) == false)
			{
				kill_everyone(d);
				usleep(1000);
				printf("%d %d has died\n", get_runtime(d->t_start), \
				(&d->philos[d->i])->num);
				return ;
			}
			if (d->num_eat < INT_MAX && check_if_saturated(&d->philos[d->i], \
			(&d->philos[d->i])->eat2, false) == true)
				return (just_for_norm(d, d->i));
			d->i++;
		}
		usleep(100);
	}
}

static int	parse_input(t_data *data, int argc, char **argv)
{
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
	if (run_threads(&data, data.philos) == -1)
	{
		clean_up(&data);
		return (4);
	}
	clean_up(&data);
	return (0);
}
