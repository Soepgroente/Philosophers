/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stalking.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/29 22:11:48 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/12 21:00:10 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_everyone(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		kill_henk(&data->philos[i], &data->philos[i].life_lock);
		i++;
	}
}

static bool	check_saturation(t_data *d)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < d->ph_num)
	{
		if (check_if_saturated(&d->philos[i], &d->philos[i].food_lock) == true)
			count++;
		i++;
	}
	if (count == d->ph_num)
	{
		kill_everyone(d);
		return (true);
	}
	return (false);
}

static bool	stalk_table(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->ph_num)
	{
		if (poke_henk(&d->philos[i], &d->philos[i].life_lock) == false)
		{
			kill_everyone(d);
			printf("%d %d has died\n", get_runtime(d->t_start), i + 1);
			return (DEATH);
		}
		i++;
	}
	return (ALIVE);
}

void	stalk_philos(t_data *d)
{
	usleep(2500);
	if (d->num_eat < INT_MAX)
	{
		while (INFINITY)
		{
			if (stalk_table(d) == DEATH)
				return ;
			if (check_saturation(d) == true)
				return ;
			usleep(500);
		}
	}
	else
	{
		while (INFINITY)
		{
			if (stalk_table(d) == DEATH)
				return ;
			usleep(500);
		}
	}
}
